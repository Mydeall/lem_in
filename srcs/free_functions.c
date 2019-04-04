/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:55:41 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 18:39:02 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_links(t_link *link)
{
	t_link	*tmp;

	while (link)
	{
		tmp = link->next;
		link->room_dest = NULL;
		free(link);
		link = NULL;
		link = tmp;
	}
}

void	free_hash_tab(t_map *map)
{
	int		i;
	t_room	*tmp;
	t_room	*room;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (map->hash_tab[i])
		{
			room = map->hash_tab[i];
			while (room)
			{
				tmp = room->next;
				free(room->name);
				free_links(room->links);
				free(room);
				room = NULL;
				room = tmp;
			}
		}
		map->hash_tab[i] = NULL;
	}
}

void	free_room(t_room *room)
{
	t_link	*current_link;
	t_link	*tmp;

	while (room->params)
		param_next(&(room->params));
	current_link = room->links;
	while (current_link)
	{
		tmp = current_link;
		current_link = current_link->next;
		free(tmp);
	}
	free(room->name);
	free(room);
}
	

void	free_map(t_map *map)
{
	int		i;
	t_room	*current_room;	
	t_room	*tmp;

	i = -1;
	while (++i < HASH_SIZE)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			tmp = current_room;		
			current_room = current_room->next;
			free_room(tmp);
		}
	}
	free(map->hash_tab);
	free(map);
}
