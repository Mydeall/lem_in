/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:04:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/03 12:59:07 by ccepre           ###   ########.fr       */
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

void		parser(t_map *map, t_tab_parser *tab_parser, char *line)
{
	char	command;
	int		error;
	int		step;
	int		ret;
	int		i;

	int		nb_line = 0;

	step = 0;
	command = 0;
	while ((ret = get_next_line(0, &line)) == 1)
	{
		nb_line++;
		i = -1;
//		printf("line %d : %s\n", nb_line, line);
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		while (++i < 4)
		{
			if (tab_parser[i].step == step || i == 0 || (i == 3 && step == 1))
			{
				error = tab_parser[i].f(line, map, &step, &command);
				//printf("line = %d\ni = %d --> error = %d\n", nb_line, i, error);
				if (error == 0 || error == -1)
					break ;
			}
		}
		free(line);
		if (error == 1 || error == -1)
			return ;
	}
	write(1, "\n", 1);
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
