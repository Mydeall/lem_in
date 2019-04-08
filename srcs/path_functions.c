/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:11:04 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/08 18:10:35 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_path(t_path *paths)
{
	int	i;

	i = -1;
	if (!paths)
		return ;
	while (paths[++i].path)
		free_queue(paths[i].path);
	free(paths);
}

t_link			*find_flow(t_link *links, int value)
{
	t_link	*current_link;

	current_link = links;
	while (current_link)
	{
		if (current_link->flow == value)
			return (current_link);
		current_link = current_link->next;
	}
	return (NULL);
}

static t_queue	*browse_path(t_map *map, t_room *current_room)
{
	t_queue	*path;
	t_link	*link;

	path = NULL;
	if (append_queue(&path, map->start))
		return (NULL);
	while (current_room != map->end)
	{
		if (append_queue(&path, current_room))
			return (NULL);
		if (!(link = find_flow(current_room->links, 1)))
			return (NULL);
		current_room = link->room_dest;
	}
	if (append_queue(&path, current_room))
		return (NULL);
	return (path);
}

static t_path	*initialize_paths(t_map *map)
{
	t_link	*current_link;
	t_path	*paths;
	int		nb_paths;

	current_link = map->start->links;
	nb_paths = 0;
	while (current_link)
	{
		if (current_link->flow == 1)
			nb_paths++;
		current_link = current_link->next;
	}
	if (!(paths = (t_path*)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	paths[nb_paths].path = NULL;
	return (paths);
}

t_path			*get_paths(t_map *map)
{
	t_link	*current_link;
	t_path	*paths;
	int		i;

	if (!(paths = initialize_paths(map)))
		return (NULL);
	current_link = map->start->links;
	i = -1;
	while (current_link)
	{
		if (current_link->flow == 1)
		{
			if (!(paths[++i].path = browse_path(map,\
							current_link->room_dest)))
			{
				free_path(paths);
				return (NULL);
			}
			paths[i].steps = 0;
			paths[i].size = 0;
			paths[i].ants = 0;
		}
		current_link = current_link->next;
	}
	return (paths);
}
