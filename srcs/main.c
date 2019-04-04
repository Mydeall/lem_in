/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 20:15:00 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	error(t_tab_parser *tab_parser, t_map *map, int error_type)
{
	if (tab_parser)
		free(tab_parser);
	if (map)
		free_map(map);
	if (error_type == 0)
		write(1, "ERROR\n", 6);
	else
		write(1, "Malloc Error\n", 13);
	return (error_type);
}

int	main(void)
{
	t_tab_parser	*tab_parser;
	t_map			*map;
	char			*line;

	line = NULL;
	map = NULL;
	tab_parser = NULL;
	if (!(tab_parser = initialize_tab_parser(tab_parser))
			|| !(map = initialize_map(map)))
		return (error(tab_parser, map, 1));
	parser(map, tab_parser, line); //gerer les differentes erreurs --> malloc 
	if (append_param(map->start, NULL, 0) || find_best_paths(map, map->start))
		return (error(tab_parser, map, 1));
	if (!map->best_paths)
		return (error(tab_parser, map, 0));
//	display_instructions(map, map->best_paths, map->best_steps);
	printf("\nBest paths after edmonds-karp :\n");
	display_paths(map->best_paths);
	printf("finale best steps : %d\n", map->best_steps);
	free_map(map);
	if (tab_parser)
		free(tab_parser);
	return (0);
}
