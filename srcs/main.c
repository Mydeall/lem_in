/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/14 13:28:02 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

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

void			print_map(t_map *map)
{
	int		i;
	t_room	*tmp;
	t_link	*tmp2;
	
	i = 0;
	printf("ants = %d\n", map->ants);
	if (map->start)
		printf("start = %s\n", map->start->name);
	else
		printf("start = %p\n", map->start);
	if (map->end)
		printf("end = %s\n", map->end->name);
	else
		printf("end = %p\n", map->end);
	while (i < HASH_SIZE)
	{
		if (map->hash_tab[i])
		{
			tmp = map->hash_tab[i];
			printf("---- CELLULE ----\n");
			while (tmp)
			{
				printf("room name = %s\n", tmp->name);
				tmp2 = tmp->links;
				if (!tmp2)
					printf("----link dest = %p\n", tmp2);
				while (tmp2)
				{
					printf("----link dest = %s\n", tmp2->room_dest->name);
					tmp2 = tmp2->next;
				}
				tmp = tmp->next;
			}
			printf("--------------\n");
		}
		i++;
	}
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
	print_map(map);
}
