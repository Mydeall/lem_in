/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_recur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 13:05:22 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/20 16:05:08 by ccepre           ###   ########.fr       */
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
	if (!(paths = (t_queue**)malloc(sizeof(t_queue*) * (nb_paths + 1))))
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

int		recur_edmonds_karp(t_map *map)
{
	int	nb_iter;
	t_queue	*current;
	t_queue	*bfs_path;
	t_queue **paths;
//	t_queue	**best_path;
	int		best_len;

	best_len = -1;
	nb_iter = 1;
	while ((bfs_path = recur_bfs(map, map->start, &best_len)))
	{
		best_len = -1;
		current = bfs_path;
		while (current->next)
		{
			update_flow(current->room, current->next->room, 1);
			update_flow(current->next->room, current->room, -1);
			current = current->next;
		}
		// free bfs_path
		if (!(paths = get_paths(map)))
			return (1);
		printf("\nafter bfs n%d :\n", nb_iter);
		display_paths(paths);
		printf("end display paths\n\n");
//		usleep(5000000);
		// comparer nb_tour apres repartition
		// +update chemins
		nb_iter++;
	}
		printf("\nafter bfs n%d :\n", nb_iter);
		display_paths(paths);
		printf("end display paths\n\n");
	if (nb_iter == 0)
		return (1);
	return (0);
}
