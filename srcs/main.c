/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 18:38:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(void)
{
	t_tab_parser	*tab_parser;
	t_map			*map;
	char			*line;
	int				ret;

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
	if ((ret = recur_edmonds_karp(map)))
	{
		if (ret == 1)
			write(1, "ERROR\n", 6);
		else
		{
			free_map(map);
			return (1);
		}
	}
	return (0);
}
