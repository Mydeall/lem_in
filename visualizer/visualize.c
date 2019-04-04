/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:56:39 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 19:11:54 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_move	*initialize_tab_ants(t_map *map)
{
	t_move	*tab_ants;
	int		i;

	if (!(tab_ants = (t_move*)malloc(sizeof(t_move) * map->ants)))
		return (NULL);
	i = -1;
	while (++i < map->ants)
	{
		tab_ants[i].room = NULL;
		tab_ants[i].room_dest = map->start;
		tab_ants[i].x = 0;
		tab_ants[i].y = 0;
	}
	return (tab_ants);
}

static t_visu	*initialize_visu(t_map *map, char **instructions)
{
	t_visu	*visu;

	if (!(visu = (t_visu*)malloc(sizeof(t_visu))))
		return (NULL);
	visu->x_min = INT_MAX;
	visu->x_max = 0;
	visu->y_min = INT_MAX;
	visu->y_max = 0;
	find_min_max_coord(map, visu);
	visu->x_diff = visu->x_max - visu->x_min;
	visu->y_diff = visu->y_max - visu->y_min;
	visu->delay = give_delay(instructions);
	give_sizes(map, visu);
	visu->follow = 1;
	visu->ants_start = 0;
	visu->ants_end = 0;
	visu->dest.w = visu->ant_size;
	visu->dest.h = visu->ant_size;
	visu->room.w = visu->square_size;
	visu->room.h = visu->square_size;
	visu->sprite = SDL_LoadBMP("./visualizer/Rond10.bmp");
	SDL_SetColorKey(visu->sprite, SDL_TRUE,
		SDL_MapRGB(visu->sprite->format, 40, 147, 255));
	return (visu);
}

static void		actualize_coor(t_map *map, t_visu *visu)
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
			current_room->x = (visu->x_diff ? 200
				+ (current_room->x - visu->x_min) * 1200 / visu->x_diff : 800);
			current_room->y = (visu->y_diff ? 150
				+ (current_room->y - visu->y_min) * 600 / visu->y_diff : 450);
			current_room = current_room->next;
		}
	}
}

void			visualize(t_map *map, char **instructions)
{
	int		current_inst;
	t_visu	*visu;
	t_move	*tab_ants;

	if (!(tab_ants = initialize_tab_ants(map))
		|| !(visu = initialize_visu(map, instructions)))
	{
		if (tab_ants)
			free(tab_ants);
		return ;
	}
	actualize_coor(map, visu);
	create_sdl_tools(visu);
	current_inst = -1;
	while (instructions[++current_inst] && visu->follow)
	{
		if (!(update_state(map, visu, instructions[current_inst], tab_ants)))
			break ;
		poll_quit(visu);
		SDL_Delay(500);
	}
	update_state(map, visu, instructions[current_inst], tab_ants);
	while (visu->follow)
		poll_quit(visu);
	destroy_sdl_tools(visu, tab_ants);
}
