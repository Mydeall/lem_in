/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:54:20 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/15 18:19:53 by rkirszba         ###   ########.fr       */
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

static int	check_next(t_map *map, t_queue **queue, int nb_iter, int *reach_end,\
		t_queue **prev_queue)
{
	t_link	*current_link;

	current_link = (*queue)->room->links;
	while (current_link)
	{
//		printf("OK APPEND QUEUE\nflow = %d | visisted (nb_iter = %d) : %d\n", current_link->flow, nb_iter, current_link->room_dest->visited);
		if (((current_link->flow == -1) || (!current_link->flow)) && current_link->room_dest->visited != nb_iter)
		{
			if ((append_queue(queue, current_link->room_dest)))
				return (1);
			if (current_link->room_dest->visited != -1)
				current_link->room_dest->prev = (*queue)->room;
			current_link->room_dest->visited = -1;
			if (current_link->room_dest == map->end)
			{
				*reach_end = 1;
				while (*queue)
				{
					(*queue)->room->visited = nb_iter;
					refresh_queue(queue, prev_queue);
				}
				break ;
			}
		}
		current_link = current_link->next;
	}
//	printf("reach check next end ? : %d\n", *reach_end);
	return (0);
}

t_link	*find_link(t_room *room, t_room *room_dest)
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

int		bfs(t_map *map, int nb_iter)
{
	t_queue	*queue;
	t_queue *prev_queue;
	t_link	*current_link;
	t_link	*prev_link;
	int		reach_end;

	reach_end = 0;
	queue = NULL;
	append_queue(&queue, map->start);
	//printf("ok bfs %d\n", nb_iter);
	while (queue)
	{
		queue->room->visited = nb_iter;
	//	printf("room : %s\n", queue->room->name);
	//	printf("room : %d\n", queue->room->visited);
		if ((current_link = find_flow(queue->room->links, -1)))
		{
			prev_link = find_link(queue->room, prev_queue->room);
			if (!prev_link->flow)
			{
			//	printf("%s : flux negatif ne venant pas d'un flux !!!!!!!!!!!!!\n", queue->room->name);
				if (current_link->room_dest->visited == nb_iter)
				{
					queue->room->visited = 0;
		//			display_queue(queue);
					refresh_queue(&queue, &prev_queue);
					continue ;
				}
				if ((append_queue(&queue, current_link->room_dest)))
					return (-1);
				if (current_link->room_dest->visited != -1)
					current_link->room_dest->prev = queue->room;
				current_link->room_dest->visited = -1;
		//		display_queue(queue);
				refresh_queue(&queue, &prev_queue);
				continue ;
			}
		}
	//	printf("ok bfs 2 %d\n", nb_iter);
		if ((check_next(map, &queue, nb_iter, &reach_end, &prev_queue)))
			return (-1);
	//	printf("before refresh\n");
	//	display_queue(queue);
		if (queue)
			refresh_queue(&queue, &prev_queue);
	//	printf("after refresh\n");
	//	display_queue(queue);
	//	printf("ok bfs 3 %p\n", queue);
	}
//	printf("reach bfs end ? : %d\n", reach_end);
	return (reach_end);
}