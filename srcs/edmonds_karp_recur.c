/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_recur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 13:05:22 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/22 15:24:50 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
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

void			update_flow_path(t_queue *path, char side)
{
	t_queue *current;
	
	current = path;
	if (!path)
		return ;
	while (current->next)
	{
		update_flow(current->room, current->next->room, side);
		update_flow(current->next->room, current->room, -side);
		current = current->next;
	}
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
		link = find_flow(current_room->links, 1);
		current_room = link->room_dest;
	}
	if (append_queue(&path, current_room))
		return(NULL);
	return (path);
}

t_path	*get_paths(t_map *map)
{
	t_link	*current_link;
	t_path	*paths;
	int		nb_paths;

	nb_paths = 0;
	current_link = map->start->links;
	while (current_link)
	{
		if (current_link->flow == 1)
			nb_paths++;
		current_link = current_link->next;
	}
	if (!(paths = (t_path*)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	paths[nb_paths].path = NULL;
	current_link = map->start->links;
	nb_paths = 0;
	while (current_link)
	{
		if (current_link->flow == 1)
		{
			if (!(paths[nb_paths].path = browse_path(map, current_link->room_dest)))
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

int		test_best_repartition(t_map *map, t_path **best_paths, int *best_steps)
{
	t_path	*paths;
	int		steps;
	int		i;

	i = -1;
	if (!(paths = get_paths(map)))
		return (1);
	steps = ants_repartition(map->ants, paths);
	display_paths(paths);
	printf("steps : %d\n", steps);
	printf("----------------\n");
	if (*best_steps == -1 || *best_steps > steps)
	{
		*best_steps = steps;
		*best_paths = paths;
		// free old best_path
	}
	else
	{
		while (paths[++i].path)
			free_queue(paths[i].path);
		free(paths);
	}
	return (0);
}

int		recur_edmonds_karp(t_map *map)
{
	t_path	*best_paths;
	int		best_steps;

	best_steps = -1;
	best_paths = NULL;
	printf("edmonds karp !\n");
	if (recur_bfs(map, map->start, &best_steps, &best_paths))
		return (1);
	printf("\nBest paths after edmonds-karp :\n");
	display_paths(best_paths);
	printf("finale best steps : %d\n", best_steps);
	if (!best_paths)
		return (1);
	return (0);
}
