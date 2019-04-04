/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_len_bfs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:36:17 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/03 17:15:17 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	find_path_flow_back(t_room *room)
{
	t_link	*link;
	t_room	*current_room;
	int		nb_room;

	current_room = room;
	nb_room = 0;
	while ((link = find_flow(current_room->links, -1)))
	{
		nb_room++;
		current_room = link->room_dest;
	}
	return (nb_room);
}

int		compute_len(t_room *start, t_room *room, int len)
{
	t_room *current;
	
	current = room;
	while (current != start && current->params->prev)
	{
		len++;
		current = current->params->prev;
	}
	return (len);
}

int		bfs_best_len(t_map *map, t_room *room_start, int *best_len,\
		t_queue **best_path)
{
	t_queue	*head_queue;
	t_queue	*queue;
	t_link	*current_link;
	int		end_reached;
	int		len;
	int		bfs_id;

	head_queue = NULL;
	append_queue(&head_queue, room_start);
	queue = head_queue;
	end_reached = 0;
	len = find_path_flow_back(room_start);
	bfs_id = room_start->params->bfs_id;
	while (queue && !end_reached && (*best_len == -1\
				|| compute_len(room_start, queue->room, len) < *best_len))
	{
		queue->room->params->visited = 1;
		current_link = find_flow(queue->room->links, -1);
		if (!verif_launch_recur(queue, map, current_link))
//		if ((current_link = find_flow(queue->room->links, -1))\
//				&& current_link->room_dest->nb_recur < 1)
		{
			current_link->room_dest->nb_recur++;
			if (append_param(current_link->room_dest, queue->room, bfs_id + 1))
				return (1);
			if (bfs_best_len(map, current_link->room_dest, best_len, best_path))
				return (1);
		}
		if (links_manager(map, &queue, &head_queue, &end_reached))
			return (1);
		queue = queue->next;
	}
	if (end_reached)
	{
		len = compute_len(room_start, queue->room, len);
		*best_len = len;
		if (!(*best_path = find_bfs_path(map, map->end)))
			return (1);
//		display_queue(*best_path);
	}
	reset_visited(&head_queue);
	return (0);
}
