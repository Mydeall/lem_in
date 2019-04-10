/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:47:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/10 16:19:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			verif_com(char *line, t_map *map, int *step, char *command)
{
	(void)step;
	(void)map;
	if (line && *line == '#')
	{
		if (*(line + 1) == '#')
		{
			if (*command || (*step != 1 && (!ft_strcmp((line + 2), "start")\
						|| !ft_strcmp((line + 2), "end"))))
				return (1);
			if (!(ft_strcmp((line + 2), "start")))
				*command = 1;
			if (!(ft_strcmp((line + 2), "end")))
				*command = 2;
		}
		return (0);
	}
	return (line ? 1 : -1);
}

int			verif_ants(char *line, t_map *map, int *step, char *command)
{
	map->ants = is_pos_int(line);
	if (map->ants == -1 || map->ants == 0 || *command)
		return (1);
	(*step)++;
	return (0);
}

static int	verif_coord(char *cp_line, t_room *room)
{
	int		i;

	i = 0;
	while (cp_line[i])
		i++;
	while (i > 0 && cp_line[i] != ' ')
		i--;
	if (!cp_line[i + 1] || (room->y = is_pos_int(&(cp_line[i + 1]))) == -1)
	{
		free(cp_line);
		free(room);
		return (1);
	}
	cp_line[i] = 0;
	while (i > 0 && cp_line[i] != ' ')
		i--;
	if (!cp_line[i + 1] || (room->x = is_pos_int(&(cp_line[i + 1]))) == -1)
	{
		free(cp_line);
		free(room);
		return (1);
	}
	cp_line[i] = 0;
	return (0);
}

static int	verif_name(t_map *map, char *cp_line, t_room *room)
{
	int		error;
	char	**name_split;
	int		i;

	error = 0;
	i = -1;
	name_split = NULL;
	if (!*cp_line || *cp_line == 'L')
		error = 1;
	else if (!(name_split = ft_strsplit(cp_line, ' ')))
		error = -1;
	else
		while (name_split && name_split[++i])
			if (*(name_split[i]) == 'L')
				error = 1;
	if (error || !(room->name = ft_strdup(cp_line)))
		error = error == 0 ? -1 : error;
	else if (append_room(room, map))
		error = 1;
	if (error)
		free(room);
	free(cp_line);
	ft_freetab(name_split);
	return (error);
}

int			verif_room(char *line, t_map *map, int *step, char *command)
{
	t_room	*room;
	char	*cp;
	int		ret;

	(void)step;
	if (!(cp = ft_strdup(line))\
			|| !(room = (t_room*)malloc(sizeof(t_room))))
		return (-1);
	room->next = NULL;
	room->links = NULL;
	room->nb_recur = 0;
	room->params = NULL;
	if (verif_coord(cp, room))
		return (1);
	if ((ret = verif_name(map, cp, room)))
		return (ret);
	if (*command == 1)
		map->start = room;
	else if (*command == 2)
		map->end = room;
	*command = 0;
	return (0);
}
