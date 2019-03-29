/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:05 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/28 18:42:14 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		parser_v(t_map *map, t_tab_parser *tab_parser, char *line)
{
	char	command;
	int		error;
	int		step;
	int		i;

	step = 0;
	command = 0;
	while ((get_next_line(0, &line)) == 1)
	{
		if (!(*line))
		{
			free(line);
			return ;
		}
		i = -1;
		while (++i < 4)
		{
			if (tab_parser[i].step == step || i == 0 || (i == 3 && step == 1))
			{
				error = tab_parser[i].f(line, map, &step, &command);
				if (error == 0 || error == -1)
					break ;
			}
		}
		free(line);
		if (error == 1 || error == -1)
			return ;
	}
}