/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:07:57 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/03 18:49:55 by ccepre           ###   ########.fr       */
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

t_queue	*find_bfs_path(t_map *map, t_room *end)
{
	t_room	*room;// if needed can supress room and use current->room
	t_param	*current;
	t_queue	*current_path;
	t_queue	*path;

	room = end;
	path = NULL;
	while (room != map->start)
	{
		current = room->params;
		current_path = path;
		while (current_path)
		{
			if (current_path->room == room)
				current = current->next;
			current_path = current_path->next;
		}
		if (append_start_queue(&path, room))
			return (NULL);
		room = current->prev;
	}
	if (append_start_queue(&path, room))
		return (NULL);
	return (path);
}

/*
t_queue	*find_bfs_path(t_map *map, t_room *end)
{
	t_room	*room;// if needed can supress room and use current->room
	t_param	*current_param;
	t_queue	*path;
	int		last_bfs_id;

	room = end;
	last_bfs_id = room->params->bfs_id;
	path = NULL;
	while (room != map->start)
	{
		current_param = room->params;
		while (current_param->bfs_id > last_bfs_id)
			current_param = current_param->next; // si segfault alors probleme d'append
		if (append_start_queue(&path, room))
			return (NULL);
		last_bfs_id = current_param->bfs_id;
		room = current_param->prev;
	}
	if (append_start_queue(&path, room))
		return (NULL);
	return (path);
}
*/

void		reset_visited(t_queue **queue)
{
	t_param	*tmp;
	t_queue	*tmp_queue;

	while (*queue)
	{
		tmp = (*queue)->room->params;
		(*queue)->room->params =  (*queue)->room->params->next;
		free(tmp);
		tmp_queue = *queue;
		*queue = (*queue)->next;
		free(tmp_queue);
	}
}
