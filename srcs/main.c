/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/05 16:06:42 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	error(t_tab_parser *tab_parser, t_map *map, char *input, int error_type)
{
	if (tab_parser)
		free(tab_parser);
	if (input)
		free(input);
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
	char			*input;

	line = NULL;
	map = NULL;
	tab_parser = NULL;
	input = ft_strnew(0);
	if (!(tab_parser = initialize_tab_parser(tab_parser))
			|| !(map = initialize_map(map)))
		return (error(tab_parser, map, input, 1));
	parser(map, tab_parser, line, &input);
	if (map->ants == -1 || !map->start || !map->end)	
		return (error(tab_parser, map, input, 0));
	if (append_param(map->start, NULL, 0) || find_best_paths(map, map->start))
		return (error(tab_parser, map, input, 1));
	if (!map->best_paths)
		return (error(tab_parser, map, input, 0));
	write(1, input, ft_strlen(input));
	/* display_instructions(map, map->best_paths, map->best_steps); */
	printf("\nBest paths after edmonds-karp :\n");
	display_paths(map->best_paths);
	printf("finale best steps : %d\n", map->best_steps);
	free_map(map);
	if (tab_parser)
		free(tab_parser);
	if (input)
		free(input);
	return (0);
}
