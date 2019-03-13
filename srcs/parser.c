/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:04:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/13 19:12:08 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_pos_int(char *str)
{
	int			len;
	long long	nb;

	len = -1;	
	if (*str == '+')
		len++;
	while (str[++len])
		if (!ft_isdigit(str[len]) || len > 12)
			return (1);
	nb = ft_atoi(str);
	if (nb <= 2147483647)
		return ((int)nb);
	return (-1);
}

int		parser(t_map *map, t_tab_parser *tab_parser)
{
	char	*line;
	char	command;
	int		error;
	int		step;
	int		ret;
	int		i;

	line = NULL;
	step = 0;
	while ((ret = get_next_line(0, &line)) == 1)
	{
		// verif com
		i = -1;
		while (++i < 4)
		{
			if (tab_parser[i].step == step || i == 0 || (i == 3 && step == 1))
			{
				error = tab_parser[i].f(line, map, &step, &command);
				if (error == 0)
					continue ;
			}
		}
	}
}


/*
		if (step == 0)
		{
			error = (map->ants = is_pos_int(line)) == -1 ? 1 : 0;
			if (!error)
			{
				step++;
				free(line);
				continue ;
			}
		}
		else if (step == 1)
			error = verif_room(line, map, step, &command);
	}
}
*/