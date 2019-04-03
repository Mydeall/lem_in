/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/03 12:05:29 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
void			display_params(t_param *params)
{
	t_param *current;

	current = params;
	printf("------ params -----\n");
	if (!current)
		printf("(null)\n");
	while (current)
	{
		printf("bfs_id : %d\n", current->bfs_id);
		if (current->prev)
			printf("prev : %s\n", current->prev->name);
		else
			printf("prev : NULL\n");
		current = current->next;
	}
	printf("---- fin params ----\n");
}
*/

int static	verif_launch_recur(t_queue *queue, t_map *map, t_link *current_link)
{
	t_queue *current;
	t_queue	*path;

	if (!current_link || current_link->room_dest->nb_recur > 100)
		return (1);
	if (!(path = find_bfs_path(map, queue->room)))
		return (1);
	current = path;
	while (current->next)
	{
		if (current->room == queue->room\
				&& current->next->room == current_link->room_dest)
			return (1);
		current = current->next;
	}
	return (0);
}

void			param_next(t_param **params)
{
	t_param	*tmp;

	if (!params || !*params)
		return ;
	tmp = *params;
	*params = (*params)->next;
	free(tmp);
}

int				append_param(t_room *room, t_room *prev, int bfs_id)
{
	t_param	*new;

	if (!(new = (t_param*)malloc(sizeof(t_param))))
		return (1);
	new->bfs_id = bfs_id;
	if (room->params)
		new->visited = room->params->visited;
	else
		new->visited = 0;
	new->prev = prev;
	new->next = room->params;
	room->params = new;
	return (0);
}

static int		link_action(t_queue **queue, t_link *link, t_map *map,\
		int *end_reached)
{
	int bfs_id;

	bfs_id = (*queue)->room->params->bfs_id;
//	if (!verif_launch_recur(*queue, map, link) && (!link->flow) && (!link->room_dest->params\
//				|| link->room_dest->params->bfs_id != bfs_id)) //chemin empreintable
//	{
	if ((!link->flow) && (!link->room_dest->params\
				|| !link->room_dest->params->visited)) //chemin empreintable
	{
		if (!(verif_already_queue(queue, link->room_dest)))
		{
			if (append_param(link->room_dest, (*queue)->room, bfs_id))
				return (1);
			if ((append_queue(queue, link->room_dest)))
				return (1);
			if (link->room_dest == map->end)
				*end_reached = 1;
		}
	}
	return (0);
}

int		links_manager(t_map *map, t_queue **queue, t_queue **head_queue,\
		int *end_reached)
{
	t_link	*current_link;
	t_link	*prev_link;
	
	if ((current_link = find_flow((*queue)->room->links, -1)))
	{
		prev_link = find_link((*queue)->room, (*queue)->room->params->prev);
		if (!prev_link->flow)
		{
			param_next(&(*queue)->room->params); //enlever de la queue si on fait ca
			remove_queue_elem(head_queue, *queue);
			return (0);
		}					
	}
	current_link = (*queue)->room->links;
	while (current_link && !*end_reached)
	{
		if (link_action(queue, current_link, map, end_reached))
			return (-1);
		current_link = current_link->next;
	}
	return (0);
}

/*
static int	verif_flow_path(t_queue *path, t_map *map)
{
	t_queue *current;
	t_link	*link;
	int 	pos;
	int 	neg;

	current = path;
	while (current)
	{
		pos = 0;
		neg = 0;
		if (current->room == map->start || current->room == map->end)
		{
			current = current->next;
			continue ;
		}
		link = current->room->links;
		while (link)
		{
			if (link->flow == 1)
				pos++;
			if (link->flow == -1)
				neg++;
			link = link->next;
		}
		if (pos != neg)
		{
			display_room(current->room);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
*/

int			recur_bfs(t_map *map, t_room *room_start, int *best_steps,\
		t_path **best_ed_paths)
{
	t_queue	*head_queue;
	t_queue	*queue;
	t_link	*current_link;
	t_queue	*bfs_path;
	t_path	*paths;
	int		end_reached;
	int		bfs_id;
	
	bfs_path = NULL;
	head_queue = NULL;
	append_queue(&head_queue, room_start);
	queue = head_queue;
	end_reached = 0;
	bfs_id = room_start->params->bfs_id;
	while (queue && !end_reached)
	{
		queue->room->params->visited = 1;
		current_link = find_flow(queue->room->links, -1);
		if (!verif_launch_recur(queue, map, current_link))
		{
			current_link->room_dest->nb_recur++;
			if (append_param(current_link->room_dest, queue->room, bfs_id + 1))
				return (1);
//			printf("Appel recur from (%s : %s) to %s\n", room_start->name,\
//					queue->room->name, current_link->room_dest->name);
			if (recur_bfs(map, current_link->room_dest, best_steps, best_ed_paths))
				return (1);
//			printf("END appel recur from (%s : %s) to %s\n", room_start->name,\
//					queue->room->name, current_link->room_dest->name);
		}
		if (links_manager(map, &queue, &head_queue, &end_reached))
			return (1);
		queue = queue->next;
	}
	if (end_reached)
		if (!(bfs_path = find_bfs_path(map, map->end)))
			return (1);
	reset_visited(&head_queue);
	if (!end_reached)
		return (0);
	if (!(paths = get_paths(map)))
		return (1);
	update_flow_path(bfs_path, 1);
	if (test_best_repartition(map, best_ed_paths, best_steps))
		return (1);
	if (append_param(map->start, NULL, bfs_id + 1))
		return (1);
	if (recur_bfs(map, map->start, best_steps, best_ed_paths))
		return (1);
	update_flow_path(bfs_path, -1);
	return (0);
}
//printf("NEW BFS on %s !\n", room_start->name);
//printf("Appel recur from %s to %s\n", room_start->name, current_link->room_dest->name);
//usleep(1000000);
//printf("Fin recur from %s to %s\n", room_start->name, current_link->room_dest->name);
//
//	if (verif_flow_path(bfs_path, map))
//	{
//		display_queue(bfs_path);
//		printf("Retour\n");
//		usleep(10000000);
//	}
