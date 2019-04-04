/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:19:01 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 20:20:45 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		hash_jenkins(char *name)
{
	int				i;
	unsigned int	hash;

	i = -1;
	hash = 0;
	while (name[++i])
	{
		hash += name[i];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return ((int)(hash % HASH_SIZE));
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

	if (!name || !(*name))
		return (NULL);
	hash = hash_jenkins(name);
	tmp = map->hash_tab[hash];
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void		update_flow(t_room *a_room, t_room *b_room, char side)
{
	t_link	*current_link;

	current_link = a_room->links;
	while (current_link)
	{
		if (current_link->room_dest == b_room)
		{
			if (current_link->flow == -1 || current_link->flow == 1)
				current_link->flow = 0;
			else
				current_link->flow = side;
			break ;
		}
		current_link = current_link->next;
	}
}

void			update_flow_path(t_queue *path, char side)
{
	t_queue *current;

	current = path;
	if (!path)
		return ;
	while (current->next)
	{
		update_flow(current->room, current->next->room, side);
		update_flow(current->next->room, current->room, -side);
		current = current->next;
	}
}
