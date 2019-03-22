/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:07:57 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/22 18:43:10 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>

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
/*
t_room	*find_next_prev(t_map *map, t_room *room, int depth)
{
	int		i;
	t_room	*current;
	t_queue	*current_prev;
	int		count;

	current = map->end;
	i = 0;
	count = 0;
	printf("verif %s, depth = %d\n", room->name, depth);
	while (current != map->start && i < depth)
	{
		if (current == room)
			count++;
		current = current->prev->room;
		i++;
	}
	current_prev = room->prev;
	printf("count = %d\n", count);
	if (count)
		display_queue(current_prev);
	while (count--)
		current_prev = current_prev->next;
	return (current_prev->room);
}
*/
t_queue	*find_bfs_path(t_map *map)
{
	t_room	*current;
	t_queue	*current_prev;
	t_queue	*path;
	int		i;

	current = map->end;
	path = NULL;
	while (current != map->start)
	{
//		printf("name : %s (prev = %s)\n", current->name, current->prev->room->name);
		if(append_start_queue(&path, current))
			return (NULL);
		i = 0;
		current_prev = current->prev;
//		printf("prev_depth : %d\n", current->prev_depth);
		while (i++ < current->prev_depth)
			current_prev = current_prev->next;
		current->prev_depth++;
		current = current_prev->room;
	}
	if (append_start_queue(&path, current))
		return (NULL);
	current_prev = path;
	// reset depth
	while (current_prev)
	{
		current_prev->room->prev_depth = 0;
		current_prev->room->nb_recur = 0;
		current_prev = current_prev->next;
	}
//	display_queue(path);
//	printf("end bfs path\n\n");
	return (path);
}

/*
   int		compute_len(t_room *start, t_room *room, int len)
   {
   t_room *current;

   current = room;
   while (current != start && current->prev)
   {
   len++;
   current = current->prev->room;
   }
   return (len);
   }
   */

void		reset_visited(t_map *map, t_queue **queue)
{
	t_queue	*tmp;
	int i;

	i = 0;
	while (*queue)
	{
		if (i != 0)
			(*queue)->room->visited = 0;
		if ((*queue)->room != map->start)
		{
			tmp = (*queue)->room->prev;
			(*queue)->room->prev =  (*queue)->room->prev->next;
			free(tmp);
		}
		tmp = *queue;
		*queue = (*queue)->next;
		free(tmp);
		i++;
	}
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

/*
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
   */
