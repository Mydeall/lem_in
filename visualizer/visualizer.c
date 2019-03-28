/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:12:55 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/26 11:56:02 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**record_instructions(void)
{
	char	*joined_insts;
	char	*tmp;
	char	**instructions;
	char	buf[1049];
	int		ret;


	if (!(joined_insts = ft_strnew(0)))
		return (NULL);
	while ((ret = read(0, buf, 1048)))
	{
		buf[ret] = '\0';
		tmp = joined_insts;
		joined_insts = ft_strjoin(joined_insts, buf);
		free(tmp);
	}
	if (!(instructions = ft_strsplit(joined_insts, '\n')))
		return (NULL);
	return (instructions);
}


int		main(void)
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
	visualize(map, instructions);
	//free
	return (0);
}