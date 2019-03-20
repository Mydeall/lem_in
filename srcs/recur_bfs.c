/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/20 14:34:12 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "lem_in.h"

static void	end_reached(t_queue **queue, int *reach_end, int nb_iter)
{
	*reach_end = 1;
	while (*queue)
	{
		(*queue)->room->visited = nb_iter;
		*queue = (*queue)->next;
	}
}

static int	normal_case(t_map *map, t_queue **queue, int nb_iter, int *reach_end)
{
	t_link	*current_link;

	current_link = (*queue)->room->links;
	while (current_link)
	{
		if (((current_link->flow == -1) || (!current_link->flow))\
				&& current_link->room_dest->visited != nb_iter) //chemin empreintable
		{
			if (verif_already_queue(queue, current_link->room_dest))
			{
				current_link = current_link->next;
				continue ;// ---> stop si deja dans la queue
			}
			if ((append_queue(queue, current_link->room_dest)))
				return (1);
			current_link->room_dest->prev = NULL;
			current_link->room_dest->prev = (*queue)->room;
			if (current_link->room_dest == map->end)
			{
				end_reached(queue, reach_end, nb_iter);
				break ;
			}
		}
		current_link = current_link->next;
	}
	if (*queue)
		*queue = (*queue)->next;
	return (0);
}

static int		case_flow_from_empty_flow(t_queue **queue, t_link *link, int nb_iter)
{
	if (link->room_dest->visited == nb_iter) // cul-de-sac = reset
	{
		(*queue)->room->visited = 0;  // reset cas particulier
		*queue = (*queue)->next;
		return (1) ;
	}
	if (verif_already_queue(queue, link->room_dest))
	{
		*queue = (*queue)->next;
		return (1) ;
	}
	if ((append_queue(queue, link->room_dest)))
		return (-1);
	link->room_dest->prev = (*queue)->room;
	*queue = (*queue)->next; 
	return (1) ;
}

int		*link_manager(t_map *map, t_room *room, int nb_iter)
{
	t_link	*current_link;
	t_link	*prev_link;
	
	while (links)
		
}

t_queue		*recur_bfs(t_map *map, t_room *room, int nb_iter, int *best_len)
{
	t_queue	*head_queue;
	t_queue	*queue;
	t_queue	*path;
	t_queue	*tmp_path;
	int		len;
	int		reach_end;

	path = NULL;
	reach_end = 0;
	head_queue = NULL;
	prev_link= NULL;
	append_queue(&head_queue, room);
	queue = head_queue;
	len = find_path_flow_back(room);
	while (queue && (*best_len == -1 || compute_len(room, queue->room, len) < *best_len))
	{
		printf("best_len : %d\n", *best_len);
//		printf("len : %d\n", compute_len(room, queue->room, len));
		display_queue(queue);
		queue->room->visited = nb_iter;
		link_manager
		if ((current_link = find_flow(queue->room->links, -1)))
		{
			// appel fct si flow && room_dest link -1 n'est pas visite
			if (current_link->room_dest->visited != nb_iter)
			{	
				current_link->room_dest->prev = queue->room;
				printf("Appel recur from %s to %s\n", room->name, current_link->room_dest->name);
				tmp_path = recur_bfs(map, current_link->room_dest, nb_iter, best_len);
				printf("Fin recur from %s to %s\n", room->name, current_link->room_dest->name);
				if (tmp_path)
					path = tmp_path;
//				else
//					queue->room->visited = 0;
			}
			// Cas classique de gestion de room avec un flux
			prev_link = find_link(queue->room, queue->room->prev);
			if (!prev_link->flow)
			{
				if (case_flow_from_empty_flow(&queue, current_link, nb_iter) == -1)
					return (NULL);
				continue ;
			}					
		}
		if ((normal_case(map, &queue, nb_iter, &reach_end)))
			return (NULL);

	}
	if (reach_end)
	{
		if (!(path = find_bfs_path(map)))
			return (NULL);
		len = compute_len(room, map->end, len);
		*best_len = len;
	}
	reset_visited(&head_queue);
	// ATTENTION retrun (NULL) en cas de malloc && path non trouve
	return (path);
}

// reinitialiser visited
// incrementer len ou calculer len
