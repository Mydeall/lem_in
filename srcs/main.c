/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/26 14:37:19 by ccepre           ###   ########.fr       */
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
	if (!(hash_tab = (t_room**)ft_memalloc(sizeof(t_room*) * HASH_SIZE)))
	{
		free(map);		
		return (NULL);
	}
	map->hash_tab = hash_tab;
	return (map);
}

int				main(void)
{
	t_tab_parser	*tab_parser;
	t_map			*map;
	char			*line;

	line = NULL;
	map = NULL;
	tab_parser = NULL;
	if (!(tab_parser = initialize_tab_parser(tab_parser))
			|| !(map = initialize_map(map)))
	{
//		free_all
		return (1);
	}
	parser(map, tab_parser, line);
//	print_map(map);
//	edmonds_karp(map);
	recur_edmonds_karp(map);
	return (0);
}
