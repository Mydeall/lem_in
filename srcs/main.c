/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/28 17:30:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
