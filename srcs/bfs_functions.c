/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:07:57 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/20 13:19:52 by ccepre           ###   ########.fr       */
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

int		compute_len(t_room *start, t_room *room, int len)
{
	t_room *current;
	
	current = room;
	while (current != start)
	{
		len++;
		printf("len name : %s\n", current->name);
		current = current->prev;
	}
	return (len);
}

void		reset_visited(t_queue **queue)
{
	t_queue	*tmp;
	
	tmp = *queue;
	*queue = (*queue)->next;
	free(tmp);
	while (*queue)
	{
		tmp = *queue;
		(*queue)->room->visited = 0;
		*queue = (*queue)->next;
		free(tmp);
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

t_queue	*find_bfs_path(t_map *map)
{
	t_room	*current;
	t_queue	*path;

	current = map->end;
	path = NULL;
	if (append_start_queue(&path, current))
		return (NULL);
	while (current != map->start)
	{
		printf("find path name : %s\n", current->prev->name);
		if(append_start_queue(&path, current->prev))
			return (NULL);
		current = current->prev;
	}
	return (path);
}
