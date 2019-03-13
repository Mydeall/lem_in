/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:19:01 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/13 18:02:37 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		hash_jenkins(char *name)
{
	int	i;
	unsigned int hash;

	i = -1;
	hash = 0;
	ft_putendl(name);
	while (name[++i])
	{
		hash += name[i];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return (int)(hash % HASH_SIZE);
}

int		append_room(t_room *room, t_map *map)
{
	t_room	*tmp;
	int		hash;

	hash = hash_jenkins(room->name);
	if (!map->hash_tab[hash])
		map->hash_tab[hash] = room;
	else
	{
		tmp = map->hash_tab[hash];
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->name, room->name))
				return (1);
			tmp = tmp->next;
		}
		if (!ft_strcmp(tmp->name, room->name))
			return (1);
		tmp->next = room;
	}
	return (0);
}

t_room	*find_room(char *name, t_map *map)
{
	int		hash;
	t_room	*tmp;

	hash = hash_jenkins(room->name);
	tmp = map->hash_tab[hash];
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, room->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
