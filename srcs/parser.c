/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:04:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/08 18:10:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			verif_link(char *line, t_map *map, int *step, char *command)
{
	int		i;
	char	*cp;
	t_room	*a_r;
	t_room	*b_r;

	i = 0;
	a_r = NULL;
	b_r = NULL;
	if (*command || !(cp = ft_strdup(line)))
		return (*command ? 1 : -1);
	while (!a_r || !b_r)
	{
		while (cp[i] && cp[i] != '-')
			i++;
		if (!line[i])
			break ;
		cp[i] = '\0';
		a_r = find_room(cp, map);
		b_r = find_room(cp + i + 1, map);
		i = line[i] ? i + 1 : i;
	}
	free(cp);
	*step = 2;
	return (line[i] ? append_links(a_r, b_r) : 1);
}

int			is_pos_int(char *str)
{
	int			len;
	int			i;
	long long	nb;

	i = 0;
	if (*str == '+' || (*str == '-' && !ft_atoi(str + 1)))
		i++;
	while (str[i] == '0')
		i++;
	len = -1;
	while (str[++len + i])
		if (!ft_isdigit(str[len + i]) || len > 12)
			return (-1);
	nb = ft_atoi(str);
	if (nb <= 2147483647)
		return ((int)nb);
	return (-1);
}

static int	input_manager(char *line, char **input, int end)
{
	static char	buff[LM_BUFF_SIZE + 1];
	static int	len_buff = 0;
	int			i;
	char		*tmp;

	if (end || ft_strlen(line) + 1 + len_buff > LM_BUFF_SIZE)
	{
		tmp = *input;
		*input = ft_strjoinarg(4, *input, buff, line, "\n");
		free(tmp);
		free(line);
		len_buff = 0;
		buff[0] = '\0';
		return (0);
	}
	i = -1;
	while (line[++i])
		buff[len_buff++] = line[i];
	buff[len_buff] = '\n';
	buff[++len_buff] = '\0';
	free(line);
	return (0);
}

static int	error_manager(int error, char *line, char **input)
{
	if (error)
	{
		free(line);
		input_manager(ft_strnew(0), input, 1);
		return (1);
	}
	if (input_manager(line, input, 0))
		return (1);
	return (0);
}

void		parser(t_map *map, t_tab_parser *tab_parser, char *line,\
		char **input)
{
	char	command;
	int		error;
	int		step;
	int		i;

	step = 0;
	command = 0;
	while ((get_next_line(0, &line)) == 1)
	{
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
		if (error_manager(error, line, input))
			return ;
	}
	input_manager(ft_strnew(0), input, 1);
}
