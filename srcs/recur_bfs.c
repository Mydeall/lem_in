/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/20 17:40:30 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "lem_in.h"

static t_queue	*end_reached(t_room *room_start, t_map *map, int len, int *best_len)
{
	t_queue *path;

	path = NULL;
	if (!(path = find_bfs_path(map)))
		return (NULL);
	*best_len = compute_len(room_start, map->end, len);
	return (path);
}

static int		link_action(t_queue **queue, t_link *link)
{
	if ((!link->flow) && link->room_dest->visited != 1) //chemin empreintable
		if (!(verif_already_queue(queue, link->room_dest)))
		{
			if ((append_queue(queue, link->room_dest)))
				return (1);
			if (append_start_queue(&link->room_dest->prev, (*queue)->room))
				return (-1); //WARNING
		}
	return (0);
}

int		links_manager(t_map *map, t_queue **queue)
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
	while (current_link)
	{
		if (link_action(queue, current_link))
			return (-1);
		if (current_link->room_dest == map->end)
			return (1);
		current_link = current_link->next;
	}
	return (0);
}

t_queue		*recur_bfs(t_map *map, t_room *room_start, int *best_len)
{
	t_queue	*head_queue;
	t_queue	*queue;
	t_link	*current_link;
	t_queue	*path;
	t_queue	*tmp_path;
	int		len;
	int		ret;

	path = NULL;
	head_queue = NULL;
	append_queue(&head_queue, room_start);
	queue = head_queue;
	len = find_path_flow_back(room_start);
	while (queue && (*best_len == -1 || compute_len(room_start, queue->room, len) < *best_len))
	{
		display_queue(queue);
		if (queue->room->prev)
			printf("queue->prev : %s\n", queue->room->prev->room->name);
		else
			printf("queue->prev : %s\n", NULL);
		queue->room->visited = 1;
		if ((current_link = find_flow(queue->room->links, -1))\
				&& current_link->room_dest->visited != 1)
		{
			if (append_start_queue(&current_link->room_dest->prev, queue->room))
				return (NULL);
			printf("Appel recur from %s to %s\n", room_start->name, current_link->room_dest->name);
//			usleep(1000000);
			tmp_path = recur_bfs(map, current_link->room_dest, best_len);
			if (tmp_path)
				path = tmp_path;
			printf("Fin recur from %s to %s\n", room_start->name, current_link->room_dest->name);
		}
		if ((ret = links_manager(map, &queue)) == 1)
		{
			path = end_reached(room_start, map, len, best_len);
			break ;
		}
		else if (ret == -1)
			return (NULL); // erreur malloc NULL....
		queue = queue->next;
	}
	printf("before reset\n");
	reset_visited(&head_queue);
	printf("end BFS\n");
	return (path);
}

//		printf("best_len : %d\n", *best_len);
//		printf("len : %d\n", compute_len(room, queue->room, len));
//		display_queue(queue);
//			appel fct si flow && room_dest link -1 n'est pas visite
	// ATTENTION retrun (NULL) en cas de malloc && path non trouve
