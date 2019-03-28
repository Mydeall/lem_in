/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:07:57 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/27 17:23:10 by ccepre           ###   ########.fr       */
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

t_queue	*find_bfs_path(t_map *map)
{
	t_room	*room;// if needed can supress room and use current->room
	t_queue	*current;
	t_queue	*current_path;
	t_queue	*path;

	room = map->end;
	path = NULL;
	while (room != map->start)
	{
		current = room->prev;
		current_path = path;
		while (current_path)
		{
			if (current_path->room == room)
				current = current->next;
			current_path = current_path->next;
		}
		if (append_start_queue(&path, room))
			return (NULL);
		room = current->room;
	}
	if (append_start_queue(&path, room))
		return (NULL);
	return (path);
}

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
		(*queue)->room->nb_recur = 0;
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
