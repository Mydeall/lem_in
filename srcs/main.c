/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 12:12:20 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_room(t_room *room)
{
	t_link	*current_link;
	t_link	*tmp;

	while (room->params)
		param_next(&(room->params));
	current_link = room->links;
	while (current_link)
	{
		tmp = current_link;
		current_link = current_link->next;
		free(tmp);
	}
	free(room->name);
	free(room);
}
	

void	free_map(t_map *map)
{
	int		i;
	t_room	*current_room;	
	t_room	*tmp;

	i = -1;
	while (++i < HASH_SIZE)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			tmp = current_room;		
			current_room = current_room->next;
			free_room(tmp);
		}
	}
	free(map->hash_tab);
	free(map);
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
		if (tab_parser)
			free(tab_parser);
		if (map)
			free_map(map);
//		free alll
		return (1);
	}
	parser(map, tab_parser, line);
	free(tab_parser);
	recur_edmonds_karp(map);
	free_map(map);
	return (0);
}
