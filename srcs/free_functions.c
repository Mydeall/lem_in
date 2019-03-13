/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:55:41 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/13 17:56:01 by rkirszba         ###   ########.fr       */
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
