/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:40:36 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/28 17:03:00 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_rooms(t_map *map, t_visu *visu)
{
	int			i;
	t_room		*current_room;
	SDL_Rect	rect;

	i = -1;
	SDL_SetRenderDrawColor(visu->renderer, 38, 81, 240, 255);
	while (++i < HASH_SIZE)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			rect.x = current_room->x - visu->square_size / 2;
			rect.y = current_room->y - visu->square_size / 2;
			rect.w = visu->square_size;
			rect.h = visu->square_size;
			SDL_RenderFillRect(visu->renderer, &rect);
			current_room = current_room->next;
		}
	}
}


static void	draw_links(t_map *map, t_visu *visu)
{
	int		i;
	t_room	*current_room;
	t_link	*current_link;

	i = -1;
	SDL_SetRenderDrawColor(visu->renderer, 253, 24, 142, 255);
	while (++i < HASH_SIZE)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			current_link = current_room->links;
			while (current_link)
			{
				SDL_RenderDrawLine(visu->renderer, current_room->x,
				current_room->y, current_link->room_dest->x,
				current_link->room_dest->y);
				current_link = current_link->next;
			}
			current_room = current_room->next;
		}
	}
}

void		draw_map(t_map *map, t_visu *visu)
{
	SDL_SetRenderDrawColor(visu->renderer, 213, 16, 69, 255);
	SDL_RenderClear(visu->renderer);
	draw_links(map, visu);
	draw_rooms(map, visu);
	SDL_RenderPresent(visu->renderer);
}