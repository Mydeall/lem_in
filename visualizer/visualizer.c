/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:12:55 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/02 17:06:38 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
//		free_all
		return (1);
	}
	parser_v(map, tab_parser, line);
	if (!(instructions = record_instructions()))
		return (1);
	SDL_Init(SDL_INIT_VIDEO);
	visualize(map, instructions);
	SDL_Quit();
	//free (notamment instructions);
	return (0);
}