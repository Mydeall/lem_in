/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:56:39 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/26 18:34:23 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*initialize_tab_ants(t_map *map)
{
	t_room	**tab_ants;
	int		i;

	if (!(tab_ants = (t_room**)malloc(sizeof(t_room*) * map->ants)))
		return (NULL);
	i = -1;
	while (++i < map->ants)
		tab_ants[i] = map->start;
	return (tab_ants);
}

static t_visu	*initialize_visu(t_map *map, char **instructions)
{
	t_visu	*visu;

	if (!(visu = (t_visu*)malloc(sizeof(t_visu))))
		return (NULL);
	find_min_max_coord(map, visu);
	visu->x_diff = visu->x_max - visu->x_min;
	visu->y_diff = visu->y_max - visu->y_min;
	visu->delay = give_delay(instructions);
	give_sizes(map, visu);
	visu->follow = 1;
	visu->ants_start = map->ants;
	visu->ants_end = 0;
	return (visu);	
}

void			actualize_coor(t_map *map, t_visu *visu)
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
			current_room->x = (visu->x_diff ? 200 + (current_room->x - visu->x_min) * 1200 / visu->x_diff
			: 800);
			current_room->y = (visu->y_diff ? 150 + (current_room->y - visu->y_min) * 600 / visu->y_diff
			: 450);
			current_room = current_room->next;
		}
	}
}

int				visualize(t_map *map, char **instructions)
{
	int		current_inst;
	t_visu	*visu;
	t_room	**tab_ants;

	if (!(tab_ants = initialize_tab_ants(map)))
		return (1);
	if (!(visu = initialize_visu(map, instructions)))
	{
		free(tab_ants)
		return (1);
	}
	actualize_coord(map, visu);
	// create window
	// create renderer
	visu->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);
	visu->renderer =  SDL_CreateRenderer(stct->window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	draw_map(map, visu);
	while (instructions[current_inst])
	{
		actualize_state(map, instructions[current_inst], tab_ants);
		/*
		if (fleche gauche)
			last_state(map, instructions[current_inst - 1], tab_ants);
			current_inst--;
			continue ;
		*/
		current_inst++;
		//delay()
	}
	//fonction free
	SDL_DestroyRenderer(visu->renderer);
	SDL_DestroyWindow(visu->window);
	return (0);
}