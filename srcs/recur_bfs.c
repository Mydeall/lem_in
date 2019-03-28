/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/28 12:58:24 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "lem_in.h"

/*
static t_queue	*end_reached(t_room *room_start, t_map *map, int len, int *best_len)
{
	t_queue *path;

	path = NULL;
	if (!(path = find_bfs_path(map)))
		return (NULL);
	best_len = compute_len();
	return (path);
}
*/

static int		link_action(t_queue **queue, t_link *link, t_map *map,\
		int *end_reached)
{
	if ((!link->flow) && link->room_dest->visited != 1) //chemin empreintable
		if (!(verif_already_queue(queue, link->room_dest)))
		{
			if ((append_queue(queue, link->room_dest)))
				return (1);
			if (append_start_queue(&link->room_dest->prev, (*queue)->room))
				return (1); //WARNING
			if (link->room_dest == map->end)
				*end_reached = 1;
		}
	return (0);
}

int		links_manager(t_map *map, t_queue **queue, int *end_reached)
{
	t_link	*current_link;
	t_link	*prev_link;
	
	if ((current_link = find_flow((*queue)->room->links, -1)))
	{
		prev_link = find_link((*queue)->room, (*queue)->room->prev->room);
		if (!prev_link->flow)
		{
			(*queue)->room->visited = 0;
			return (0);
		}					
	}
	current_link = (*queue)->room->links;
	while (current_link && !*end_reached)
	{
//		printf("room vu : %s\n", current_link->room_dest->name);
		if (link_action(queue, current_link, map, end_reached))
			return (1);
		current_link = current_link->next;
	}
	return (0);
}

int			recur_bfs(t_map *map, t_room *room_start, int *best_steps,\
		t_path **best_ed_paths)
{
	t_queue	*head_queue;
	t_queue	*queue;
	t_link	*current_link;
	t_queue	*bfs_path;
	int		end_reached;

	bfs_path = NULL;
	head_queue = NULL;
	append_queue(&head_queue, room_start);
	queue = head_queue;
	end_reached = 0;
	while (queue && !end_reached)
	{
//		display_queue(queue);
		queue->room->visited = 1;
//		if ((current_link = find_flow(queue->room->links, -1))\
//				&& current_link->room_dest->visited != 1)
		if ((current_link = find_flow(queue->room->links, -1))\
				&& current_link->room_dest->nb_recur < 1)
		{
			if (append_start_queue(&current_link->room_dest->prev, queue->room))
				return (1);
	//		printf("Appel recur from (%s : %s) to %s\n", room_start->name, queue->room->name, current_link->room_dest->name);
			current_link->room_dest->nb_recur++;
			if (recur_bfs(map, current_link->room_dest, best_steps, best_ed_paths))
				return (1);
//			printf("FIN recur from (%s : %s) to %s\n", room_start->name, queue->room->name, current_link->room_dest->name);
		}
		if (links_manager(map, &queue, &end_reached))
			return (1);
//		printf("end link manager\n");
		queue = queue->next;
	}
	if (end_reached)
		if (!(bfs_path = find_bfs_path(map)))
			return (1);
	reset_visited(map, &head_queue);
	if (!(end_reached))
		return (0);
	update_flow_path(bfs_path, 1);
	if (test_best_repartition(map, best_ed_paths, best_steps))
		return (1);
	if (recur_bfs(map, map->start, best_steps, best_ed_paths))
		return (1);
	update_flow_path(bfs_path, -1);
	return (0);
}

//printf("Appel recur from %s to %s\n", room_start->name, current_link->room_dest->name);
//usleep(1000000);
//printf("Fin recur from %s to %s\n", room_start->name, current_link->room_dest->name);
