/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:12:55 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 19:12:54 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_instructions(char **instructions)
{
	int		i;

	if (!instructions)
		return ;
	i = -1;
	while (instructions[++i])
		free(instructions[i]);
	free(instructions);
}

static char	**record_instructions(void)
{
	char	*joined_insts;
	char	*line;
	char	*tmp;
	char	*tmp2;
	char	**instructions;

	if (!(joined_insts = ft_strnew(0)))
		return (NULL);
	while (get_next_line(0, &line) == 1)
	{
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		tmp = joined_insts;
		tmp2 = line;
		joined_insts = ft_strjoin(joined_insts, line);
		free(tmp);
		free(tmp2);
	}
	if (!(instructions = ft_strsplit(joined_insts, '\n')))
		return (NULL);
	free(joined_insts);
	return (instructions);
}

int			main(void)
{
	t_tab_parser	*tab_parser;
	t_map			*map;
	char			*line;
	char			**instructions;

	line = NULL;
	map = NULL;
	tab_parser = NULL;
	if (!(tab_parser = initialize_tab_parser(tab_parser))
			|| !(map = initialize_map(map)))
	{
		if (tab_parser)
			free(tab_parser);
		return (1);
	}
	parser_v(map, tab_parser, line);
	if (!(instructions = record_instructions()))
		return (1);
	SDL_Init(SDL_INIT_VIDEO);
	visualize(map, instructions);
	SDL_Quit();
	free(tab_parser);
	free_map(map);
	free_instructions(instructions);
	return (0);
}
