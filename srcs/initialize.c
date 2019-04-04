/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:30:13 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 19:30:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tab_parser	*initialize_tab_parser(t_tab_parser *tab_parser)
{
	if (!(tab_parser = (t_tab_parser*)malloc(sizeof(t_tab_parser) * 4)))
		return (NULL);
	tab_parser[0].step = 0;
	tab_parser[0].f = &verif_com;
	tab_parser[1].step = 0;
	tab_parser[1].f = &verif_ants;
	tab_parser[2].step = 1;
	tab_parser[2].f = &verif_room;
	tab_parser[3].step = 2;
	tab_parser[3].f = &verif_link;
	return (tab_parser);
}

t_map			*initialize_map(t_map *map)
{
	t_room	**hash_tab;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->ants = 0;
	map->start = NULL;
	map->end = NULL;
	map->best_steps = -1;
	map->best_paths = NULL;
	if (!(hash_tab = (t_room**)ft_memalloc(sizeof(t_room*) * HASH_SIZE)))
	{
		free(map);
		return (NULL);
	}
	map->hash_tab = hash_tab;
	return (map);
}
