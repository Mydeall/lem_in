/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:07:57 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/20 17:48:10 by ccepre           ###   ########.fr       */
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
		printf("find path name : %s\n", current->prev->room->name);
		if(append_start_queue(&path, current->prev->room))
			return (NULL);
		current = current->prev->room;
	}
	return (path);
}

int		compute_len(t_room *start, t_room *room, int len)
{
	t_room *current;
	
	current = room;
	while (current != start && current->prev)
	{
		len++;
		printf("len name : %s\n", current->name);
		current = current->prev->room;
	}
	return (len);
}

void		reset_visited(t_queue **queue)
{
	t_queue	*tmp;
	int i;
	
	i = 0;
	while (*queue)
	{
		if (i != 0)
			(*queue)->room->visited = 0;
		if ((*queue)->room->prev)
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
