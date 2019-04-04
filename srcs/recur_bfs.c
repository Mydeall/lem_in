/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 18:22:27 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	link_action(t_queue **queue, t_link *link, t_map *map,\
		int *end_reached)
{
	int	depth;

	depth = (*queue)->room->params->depth;
	if ((!link->flow) && (!link->room_dest->params\
				|| link->room_dest->params->depth != depth))
	{
		if (!(verif_already_queue(queue, link->room_dest)))
		{
			if (append_param(link->room_dest, (*queue)->room, depth))
				return (1);
			if ((append_queue(queue, link->room_dest)))
				return (1);
			if (link->room_dest == map->end)
				*end_reached = 1;
		}
	}
	return (0);
}

int			links_manager(t_map *map, t_queue **queue, t_queue **head_queue,\
		int *end_reached)
{
	t_link	*current_link;
	t_link	*prev_link;
	t_queue	*tmp;

	if ((current_link = find_flow((*queue)->room->links, -1)))
	{
		prev_link = find_link((*queue)->room, (*queue)->room->params->prev);
		if (!prev_link->flow)
		{
			param_next(&(*queue)->room->params);
			tmp = *queue;
			*queue = (*queue)->next;
			remove_queue_elem(head_queue, tmp);
			return (0);
		}
	}
	current_link = (*queue)->room->links;
	while (current_link && !*end_reached)
	{
		if (link_action(queue, current_link, map, end_reached))
			return (1);
		current_link = current_link->next;
	}
	*queue = (*queue)->next;
	return (0);
}

static int	bfs(t_map *map, t_queue *head_queue, int *end_reached)
{
	int		depth;
	t_link	*current_link;
	t_queue	*queue;

	queue = head_queue;
	depth = queue->room->params->depth;
	*end_reached = 0;
	while (queue && !*end_reached)
	{
		current_link = find_flow(queue->room->links, -1);
		if (!verif_launch_recur(queue, map, current_link))
		{
			current_link->room_dest->nb_recur++;
			if (append_param(current_link->room_dest, queue->room, depth))
				return (1);
			if (find_best_paths(map, current_link->room_dest))
				return (1);
		}
		if (links_manager(map, &queue, &head_queue, end_reached))
			return (1);
	}
	return (0);
}

int			find_best_paths(t_map *map, t_room *room_start)
{
	t_queue	*head_queue;
	t_queue	*bfs_path;
	int		end_reached;
	int		depth;

	head_queue = NULL;
	depth = room_start->params->depth;
	if (append_queue(&head_queue, room_start)\
			|| bfs(map, head_queue, &end_reached))
		return (1);
	if (end_reached)
		if (!(bfs_path = find_bfs_path(map, map->end)))
			return (1);
	reset_visited(&head_queue);
	if (!end_reached)
		return (0);
	update_flow_path(bfs_path, 1);
	if (test_best_repartition(map))
		return (1);
	if (append_param(map->start, NULL, depth + 1)\
			|| find_best_paths(map, map->start))
		return (1);
	update_flow_path(bfs_path, -1);
	free_queue(bfs_path);
	return (0);
}
