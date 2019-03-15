/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:31:52 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/15 14:57:11 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	update_flow(t_room *a_room, t_room *b_room, char side)
{
	t_link	*current_link;

	current_link = a_room->links;
	while (current_link)
	{
		if (current_link->room_dest == b_room)
		{
			if (current_link->flow == -1 || current_link->flow == 1)
				current_link->flow = 0;
			else
				current_link->flow = side;
			break ;
		}
		current_link = current_link->next;
	}
}

static t_queue	*browse_path(t_map *map, t_room *current_room)
{
	t_queue	*path;
	t_link	*link;
	
	path = NULL;
	while (current_room != map->end)
	{
		if (append_queue(&path, current_room))
			return (NULL);
		link = find_flow(current_room->links, 0, 1);
		current_room = link->room_dest;
	}
	if (append_queue(&path, current_room))
		path = NULL;
	return (path);
}

static t_queue	**get_paths(t_map *map)
{
	t_link	*current_link;
	t_queue	**paths;
	int		nb_paths;

	nb_paths = 0;
	current_link = map->start->links;
	while (current_link)
	{
		if (current_link->flow == 1)
			nb_paths++;
		current_link = current_link->next;
	}
	if (!(paths = (t_queue**)malloc(sizeof(t_queue*) * (nb_paths + 1))));
		return (NULL);
	paths[nb_paths] = NULL;
	current_link = map->start->links;
	nb_paths = 0;
	while (current_link)
	{
		if (current_link->flow == 1)
		{
			if (!(paths[nb_paths] = browse_path(map, current_link->room_dest)))
			{
				//free
				return (NULL);
			}
			nb_paths++;
		}
		current_link = current_link->next;
	}
	return (paths);
}

int		edmonds_karp(t_map *map)
{
	int	nb_iter;
	t_room	*current;
	int	ret;
	t_queue **paths;

	nb_iter = 0;
	while ((ret = bfs(map, nb_iter)) == 1)
	{
		nb_iter++;
		current = map->end;
		while (current != map->start)
		{
			update_flow(current->prev, current, 1);
			update_flow(current, current->prev, -1);
			current = current->prev;
		}
		if (!(paths = get_paths(map)))
			return (1);
		// comparer nb_tour apres repartition
		// +update chemins
	}
	if (nb_iter == 0 || ret == -1)
		return (1);
	return (0);
}
