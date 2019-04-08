/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:12:55 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/05 17:53:00 by rkirszba         ###   ########.fr       */
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

static void	free_manager(t_map *map, t_tab_parser *tab_parser, char *line,
char **instructions)
{
	if (map)
		free_map(map);
	if (tab_parser)
		free(tab_parser);
	if (line)
		free(line);
	if (instructions)
		free_instructions(instructions);
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

static int	check_nb_rooms(t_map *map)
{
	int		i;
	int		nb_rooms;
	int		error;
	t_room	*current_room;

	nb_rooms = 0;
	error = 0;
	i = -1;
	while (++i < HASH_SIZE && !error)
	{
		current_room = NULL;
		if (map->hash_tab[i])
			current_room = map->hash_tab[i];
		while (current_room)
		{
			if (++nb_rooms > 30)
				error = 1;
			current_room = current_room->next;
		}
	}
	return (error ? 0 : 1);
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
	instructions = NULL;
	if (!(tab_parser = initialize_tab_parser(tab_parser))
			|| !(map = initialize_map(map))
			|| !(parser_v(map, tab_parser, line))
			|| !(instructions = record_instructions())
			|| !(check_nb_rooms(map)))
	{
		ft_printf("Your map is not correct or contains more than 30 rooms\n");
		free_manager(map, tab_parser, line, instructions);
		return (1);
	}
	SDL_Init(SDL_INIT_VIDEO);
	visualize(map, instructions);
	SDL_Quit();
	free_manager(map, tab_parser, line, instructions);
	return (0);
}
