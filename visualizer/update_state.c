/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:50:35 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/29 11:33:47 by rkirszba         ###   ########.fr       */
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
		tab_ants[i].x = (tab_ants[i].room_dest->y - tab_ants[i].room->y)
		/ MOVE_STEPS;
	}
}

static int	find_new_room_dest(t_map *map, t_visu *visu, char *instruction, t_move *tab_ants)
{
	int		i;
	char	**split;

	(void)visu;
	i = -1;
	while (++i < map->ants)
	{
		if (tab_ants[i].room_dest)
			tab_ants[i].room = tab_ants[i].room_dest;
		tab_ants[i].room_dest = NULL;
//		ft_putendl("TEST10");
	}
	// suite grace aux instruction
	//		if (tab_ants[i].room = map->start)
	//			visu.ants_start--;
	if (!(split = ft_strsplitstr(instruction, " L")))
		return (0);
	i = -1;
//	ft_putendl("TEST2");
	while (split[++i])
	{
		if (!i)
			(split[i])++;
		tab_ants[ft_atoi(split[i]) - 1].room_dest = find_room(ft_strchr(split[i], '-') + 1, map);
//		free(!i ? split[i]-- : split[i]);
	}
//	free(split);
	return (1);
}

static void	make_movement(t_visu *visu, t_move *tab_ants, int ants)
{
	SDL_Texture	*texture;
	SDL_Rect	dest;
	int			i;
	int			step;
	static int	nb_inst = 0;

	step = 0;
	while (++step < MOVE_STEPS - 1 && nb_inst)
	{
		texture = SDL_CreateTextureFromSurface(visu->renderer, visu->sprite);
		i = -1;
		while (++i < ants)
		{
			if (tab_ants[i].room)
			{
				dest.x = tab_ants[i].room->x - visu->ant_size / 2 + i * tab_ants[i].x;
				dest.y = tab_ants[i].room->y - visu->ant_size / 2 + i * tab_ants[i].y;
				dest.w = visu->ant_size;
				dest.h = visu->ant_size;
				SDL_RenderCopy(visu->renderer, texture, NULL, &dest);
//				ft_putendl("TEST");
				SDL_DestroyTexture(texture);
			}
		}
		SDL_RenderPresent(visu->renderer);
//		while (visu->current_time < visu->last_time + (500 / MOVE_STEPS))
//		{
//
//		}
		SDL_Delay(1000);
		//SDL_Delay(500 / MOVE_STEPS);
	}
	i = -1;
	while (++i < ants)
	{
		texture = SDL_CreateTextureFromSurface(visu->renderer, visu->sprite);
		dest.x = tab_ants[i].room_dest ? tab_ants[i].room_dest->x - visu->ant_size / 2
		: tab_ants[i].room->x - visu->ant_size / 2;
		dest.y = tab_ants[i].room_dest ? tab_ants[i].room_dest->y - visu->ant_size / 2
		: tab_ants[i].room->y - visu->ant_size / 2;
		dest.w = visu->ant_size;
		dest.h = visu->ant_size;
		SDL_RenderCopy(visu->renderer, texture, NULL, &dest);
		SDL_DestroyTexture(texture);
	}
	SDL_RenderPresent(visu->renderer);
//	SDL_Delay(500 / MOVE_STEPS);
	SDL_Delay(1000);
	nb_inst++;
}

int		update_state(t_map *map, t_visu *visu, char *instruction, t_move *tab_ants)
{
	int		i;
	
	give_vectors(tab_ants, map->ants);
	make_movement(visu, tab_ants, map->ants);
	i = -1;
	while (++i < map->ants)
	{
		tab_ants[i].x = 0;
		tab_ants[i].y = 0;
	}
	if (!(find_new_room_dest(map, visu, instruction, tab_ants)))
		return (0);
	return (1);
}