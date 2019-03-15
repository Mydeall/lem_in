/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:54:20 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/15 14:55:41 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link		*find_flow(t_link *links, int nb_iter, int value)
{
	t_link	*current_link;

	current_link = links;
	while (current_link)
	{
		if (current_link->flow == value\
				&& (value != -1 || current_link->room_dest->visited != nb_iter))
			return (current_link);
		current_link = current_link->next;
	}
	return (NULL);
}

static int	check_next(t_map *map, t_queue *queue, int nb_iter, int *reach_end)
{
	t_link	*current_link;

	current_link = queue->room->links;
	while (current_link)
	{
		if (!current_link->flow && current_link->room_dest->visited != nb_iter)
		{
			if ((append_queue(queue, current_link->room_dest)))
				return (1);
			current_link->room_dest->prev = queue;
			if (current_link->room_dest == map->end)
			{
				*reach_end = 1;
				while (queue)
					refresh_queue(&queue);
				break ;
			}
		}
		current_link = current_link->next;
	}
	return (0);
}

int		bfs(t_map *map, int nb_iter)
{
	t_queue	*queue;
	t_room	*tmp;
	t_link	*current_link;
	int		reach_end;

	reach_end = 0;
	queue = NULL;
	append_queue(&queue, map->start);
	while (queue)
	{
		queue->room->visited = nb_iter;
		if ((current_link = find_flow(queue->room->links, nb_iter, -1)))
		{
			if ((append_queue(queue, current_link->room_dest)))
				return (-1);
			current_link->room_dest->prev = queue;
			refresh_queue(&queue);
			continue ;
		}
		if ((check_next(map, queue, nb_iter, &reach_end)))
			return (-1);
		refresh_queue(&queue);
	}
	return (reach_end);
}