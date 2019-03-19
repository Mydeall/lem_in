/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:54:20 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/19 13:11:55 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link		*find_flow(t_link *links, int value)
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

static t_link	*find_link(t_room *room, t_room *room_dest)
{
	t_link *current_link;

	current_link = room->links;
	while (current_link)
	{
		if (current_link->room_dest == room_dest)
			return (current_link);
		current_link = current_link->next;
	}
	return (NULL);
}

static void	end_reached(t_queue **queue, int *reach_end, int nb_iter)
{
	*reach_end = 1;
	while (*queue)
	{
		(*queue)->room->visited = nb_iter;
		refresh_queue(queue);
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
				continue ;// ---> stop si deja dans la queue
			if ((append_queue(queue, current_link->room_dest)))
				return (1);
			current_link->room_dest->prev = (*queue)->room;
			if (current_link->room_dest == map->end)
			{
				end_reached(queue, reach_end, nb_iter);
				break ;
			}
		}
		current_link = current_link->next;
	}
	if (queue)
		refresh_queue(queue);
	return (0);
}

int		case_flow_from_empty_flow(t_queue **queue, t_link *link, int nb_iter)
{
	if (link->room_dest->visited == nb_iter) // cul-de-sac = reset
	{
		(*queue)->room->visited = 0;
		refresh_queue(queue);
		return (1) ;
	}
	if (verif_already_queue(queue, link->room_dest))
		return (1) ;
	if ((append_queue(queue, link->room_dest)))
		return (-1);
	link->room_dest->prev = (*queue)->room;
	refresh_queue(queue);
	return (1) ;

}

int		bfs(t_map *map, int nb_iter)
{
	t_queue	*queue;
	t_link	*current_link;
	t_link	*prev_link;
	int		reach_end;

	reach_end = 0;
	queue = NULL;
	prev_link= NULL;
	append_queue(&queue, map->start);
	while (queue)
	{
		queue->room->visited = nb_iter;
		if ((current_link = find_flow(queue->room->links, -1)))
		{
			prev_link = find_link(queue->room, queue->room->prev);
			if (!prev_link->flow)
			{
				if (case_flow_from_empty_flow(&queue, current_link, nb_iter) == -1)
					return (-1);
				continue ;
			}					
		}
		if ((normal_case(map, &queue, nb_iter, &reach_end)))
			return (-1);
	}
	return (reach_end);
}
/*
				printf("queue->room = %s\n", queue->room->name);
				printf("prev_queue->room = %s\n", prev_queue->room->name);
				printf("prev_link->flow : %d\n", prev_link->flow);
*/
