/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:11:19 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 15:26:56 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_sdl_tools(t_visu *visu)
{
	visu->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);
	visu->renderer =  SDL_CreateRenderer(visu->window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	visu->texture = SDL_CreateTextureFromSurface(visu->renderer, visu->sprite);
	SDL_FreeSurface(visu->sprite);
}

void	destroy_sdl_tools(t_visu *visu)