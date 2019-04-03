/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_nb_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:38:45 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/30 15:12:16 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		count_ants(t_map *map, t_visu *visu, t_move *tab_ants)
{
	int		i;
	
	i = -1;
	while (++i > map->ants)
	{
		if (tab_ants[i].room_dest == map->start
			|| (tab_ants[i].room == map->start && tab_ants[i].room_dest == NULL))
			visu->ants_start++;
		if (tab_ants[i].room_dest == map->end
			|| (tab_ants[i].room == map->end && tab_ants[i].room_dest == NULL))
			visu->ants_start++;
	}
}

static char	*fill_text(int ants, int room)
{
	char	*text;
	char	*nb_ants;
	char	*tmp;

	if (!(text = (char*)malloc(sizeof(char) * 9)))
		return (NULL);
	if (!room)
		text = ft_strcpy(text, "start = ");
	else
		text = ft_strcpy(text, "end =   ");
	if (!(nb_ants = ft_itoa(ants)))
	{
		free(text);
		return (NULL);
	}
	tmp = text;
	if (!(text = ft_strjoin(text, nb_ants)))
	{
		free(tmp);
		free(nb_ants);
	}
	return (text);
}

static void	fill_buffer_ants(t_visu *visu, char *text, int room)
{
	SDL_Texture	*texture;
	SDL_Color	color = {255, 255, 255, 255};
	SDL_Rect	dest;
	
//	color = {255, 255, 255, 255};
	visu->ants = TTF_RenderText_Solid(visu->font, text, color);
	texture = SDL_CreateTextureFromSurface(visu->renderer, visu->ants);
	SDL_FreeSurface(visu->ants);
	dest.x = 0;
	dest.y = (!room ? 0 : 40);
	SDL_RenderCopy(visu->renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

int			display_nb_ants(t_visu *visu)
{
	char	*text;

	if (!(text = fill_text(visu->ants_start, 0)))
		return (0);
	fill_buffer_ants(visu, text, 0);
	free(text);
	if (!(text = fill_text(visu->ants_end, 1)))
		return (0);
	fill_buffer_ants(visu, text, 1);
	free(text);
	return (1);
}