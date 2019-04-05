/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:05 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/05 17:31:56 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parser_v(t_map *map, t_tab_parser *tab_parser, char *line)
{
	char	command;
	int		error;
	int		step;
	int		i;

	step = 0;
	command = 0;
	while ((get_next_line(0, &line)) == 1)
	{
		if (!ft_strcmp(line, "ERROR"))
			return (0);
		if (!(*line))
			return (1);
		i = -1;
		while (++i < 4)
			if (tab_parser[i].step == step || i == 0 || (i == 3 && step == 1))
				if ((error = tab_parser[i].f(line, map, &step, &command) != 1))
					break ;
		free(line);
		if (error == -1)
			return (0);
	}
	line = NULL;
	return (1);
}
