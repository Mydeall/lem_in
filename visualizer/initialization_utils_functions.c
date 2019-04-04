/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_utils_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:49:49 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 19:05:22 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_min_max_coord(t_map *map, t_visu *visu)
{
	int		i;
	t_room	*current_room;

	i = -1;
	while (++i < HASH_SIZE)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			if (current_room->x < visu->x_min)
				visu->x_min = current_room->x;
			if (current_room->x > visu->x_max)
				visu->x_max = current_room->x;
			if (current_room->y < visu->y_min)
				visu->y_min = current_room->y;
			if (current_room->y > visu->y_max)
				visu->y_max = current_room->y;
			current_room = current_room->next;
		}
	}
}

int		give_delay(char **instructions)
{
	int		nb_inst;
	int		delay;

	nb_inst = 0;
	while (instructions[nb_inst])
		nb_inst++;
	if (!nb_inst)
		nb_inst++;
	delay = 10000 / nb_inst;
	return (delay);
}

void	give_sizes(t_map *map, t_visu *visu)
{
	int		nb_rooms;
	int		i;
	t_room	*current_room;

	nb_rooms = 0;
	i = -1;
	while (++i < HASH_SIZE)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			nb_rooms++;
			current_room = current_room->next;
		}
	}
	visu->square_size = 50;
	visu->ant_size = visu->square_size / 2;
}
