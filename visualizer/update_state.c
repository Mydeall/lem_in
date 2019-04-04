/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:50:35 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 19:13:58 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	give_vectors(t_move *tab_ants, int ants)
{
	int		i;

	i = -1;
	while (++i < ants)
	{
		if (!tab_ants[i].room || !tab_ants[i].room_dest)
			continue ;
		tab_ants[i].x = (tab_ants[i].room_dest->x - tab_ants[i].room->x)
			/ MOVE_STEPS;
		tab_ants[i].y = (tab_ants[i].room_dest->y - tab_ants[i].room->y)
			/ MOVE_STEPS;
	}
}

static int	find_new_room_dest(t_map *map, char *instruction, t_move *tab_ants)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < map->ants)
	{
		if (tab_ants[i].room_dest)
			tab_ants[i].room = tab_ants[i].room_dest;
		tab_ants[i].room_dest = NULL;
	}
	if (!(instruction))
		return (1);
	if (!(split = ft_strsplitstr(instruction, " L")))
		return (0);
	i = -1;
	while (split[++i])
	{
		if (!i)
			(split[i])++;
		tab_ants[ft_atoi(split[i]) - 1].room_dest = find_room(\
				ft_strchr(split[i], '-') + 1, map);
		free(!i ? (split[i] = split[i] - 1) : split[i]);
	}
	free(split);
	return (1);
}

static void	move_ants(t_map *map, t_visu *visu, t_move *tab_ants, int step)
{
	int		i;

	i = -1;
	draw_map(map, visu);
	while (++i < map->ants)
	{
		if (tab_ants[i].room)
		{
			visu->dest.x = tab_ants[i].room->x - visu->ant_size / 2
				+ step * tab_ants[i].x;
			visu->dest.y = tab_ants[i].room->y - visu->ant_size / 2
				+ step * tab_ants[i].y;
			SDL_RenderCopy(visu->renderer, visu->texture, NULL, &(visu->dest));
		}
	}
	SDL_RenderPresent(visu->renderer);
	SDL_Delay(200 / MOVE_STEPS);
}

static int	make_movement(t_map *map, t_visu *visu, t_move *tab_ants, int ants)
{
	int			i;
	int			step;
	static int	nb_inst = 0;

	step = 0;
	while (++step < MOVE_STEPS - 1 && nb_inst)
		move_ants(map, visu, tab_ants, step);
	i = -1;
	draw_map(map, visu);
	while (++i < ants)
	{
		visu->dest.x = tab_ants[i].room_dest ? tab_ants[i].room_dest->x
			- visu->ant_size / 2 : tab_ants[i].room->x - visu->ant_size / 2;
		visu->dest.y = tab_ants[i].room_dest ? tab_ants[i].room_dest->y
		- visu->ant_size / 2 : tab_ants[i].room->y - visu->ant_size / 2;
		SDL_RenderCopy(visu->renderer, visu->texture, NULL, &(visu->dest));
	}
	SDL_RenderPresent(visu->renderer);
	SDL_Delay(200 / MOVE_STEPS);
	nb_inst++;
	return (1);
}

int			update_state(t_map *map, t_visu *visu, char *instruction,
t_move *tab_ants)
{
	int		i;

	if (!visu->follow)
		return (0);
	give_vectors(tab_ants, map->ants);
	if (!(make_movement(map, visu, tab_ants, map->ants)))
		return (0);
	i = -1;
	while (++i < map->ants)
	{
		tab_ants[i].x = 0;
		tab_ants[i].y = 0;
	}
	if (!(find_new_room_dest(map, instruction, tab_ants)))
		return (0);
	return (1);
}
