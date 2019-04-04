/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:04:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 19:16:55 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		verif_link(char *line, t_map *map, int *step, char *command)
{
	int		i;
	char	*cp;
	t_room	*a_r;
	t_room	*b_r;

	i = 0;
	a_r = NULL;
	b_r = NULL;
	while (1)
	{
		if (!(cp = ft_strdup(line)) || *command)
			return (cp ? 1 : -1);
		while (cp[i] && cp[i] != '-')
			i++;
		if (!line[i])
			return (1);
		cp[i] = '\0';
		if ((a_r = find_room(cp, map))\
				&& (b_r = find_room(cp + i + 1, map)))
			break ;
		i = line[i] ? i + 1 : i;
		free(cp);
	}
	free(cp);
	*step = 2;
	return (append_links(a_r, b_r));
}

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

void	parser(t_map *map, t_tab_parser *tab_parser, char *line)
{
	char	command;
	int		error;
	int		step;
	int		ret;
	int		i;

	step = 0;
	command = 0;
	while ((ret = get_next_line(0, &line)) == 1)
	{
		i = -1;
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
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
	write(1, "\n", 1);
}
