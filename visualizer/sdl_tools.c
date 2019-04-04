/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:11:19 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 19:07:08 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_sdl_tools(t_visu *visu)
{
	visu->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);
	visu->renderer = SDL_CreateRenderer(visu->window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	visu->texture = SDL_CreateTextureFromSurface(visu->renderer, visu->sprite);
	SDL_FreeSurface(visu->sprite);
}

void	destroy_sdl_tools(t_visu *visu, t_move *tab_ants)
{
	SDL_DestroyTexture(visu->texture);
	SDL_DestroyRenderer(visu->renderer);
	SDL_DestroyWindow(visu->window);
	free(visu);
	free(tab_ants);
}

void	poll_quit(t_visu *visu)
{
	SDL_PollEvent(&(visu->event));
	if (visu->event.type == SDL_QUIT)
		visu->follow = 0;
}
