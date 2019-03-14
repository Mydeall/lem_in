/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:47:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/14 18:01:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		verif_com(char *line, t_map *map, int *step, char *command)
{
	(void)step;
	(void)map;
	if (line && *line == '#')
	{
		if (*(line + 1) == '#')
		{
			if (!(ft_strcmp((line + 2), "start")))
				*command = 1;
			if (!(ft_strcmp((line + 2), "end")))
				*command = 2;
		}
		return (0);
	}
	return (line ? 1 : -1);
}

int		verif_ants(char *line, t_map *map, int *step, char *command)
{
	if ((map->ants = is_pos_int(line)) == -1 || *command)
		return (1);
	(*step)++;
	return (0);
}

static int		verif_coord(char *cp_line, t_room *room)
{
	int		i;

	i = 0;	
	while (cp_line[i])
		i++;
	while (i > 0 && cp_line[i] != ' ')
		i--;
	if (!cp_line[i + 1] || (room->y = is_pos_int(&(cp_line[i + 1]))) == - 1)
		return (1);
	cp_line[i] = 0;
	while (i > 0 && cp_line[i] != ' ')
		i--;
	if (!cp_line[i + 1] || (room->x = is_pos_int(&(cp_line[i + 1]))) == - 1)
		return (1);
	cp_line[i] = 0;
	return (0);
}

static int		verif_name(t_map *map, char *cp_line, t_room *room)
{
	//char	*tmp; /**/
	int		error;

	error = 0;
	//tmp = cp_line; /**/
	//cp_line = ft_strtrimchar(cp_line, ' '); /**/
	//free(tmp); /**/
	if (!*cp_line)
		error = 1;
	else if (!(room->name = ft_strdup(cp_line)))
		error = -1;
	else if (append_room(room, map))
		error = 1;
	if (error)
		free(room);
	free(cp_line);
	return (error);
}

int		verif_room(char *line, t_map *map, int *step, char *command)
{
	int		i;
	t_room	*room;
	char	*cp;
	int		ret;

	(void)step;
	i = 0;
	if (!(cp = ft_strdup(line))	|| !(room = (t_room*)malloc(sizeof(t_room))))
		return(-1);
	room->next = NULL;
	room->links = NULL;
	if (verif_coord(cp, room))
		return (1);
	if ((ret = verif_name(map, cp,room)))
		return (ret);
	if (*command == 1)
		map->start = room;
	else if (*command == 2)
		map->end = room;
	*command = 0;
	return (0);
}

int		verif_link(char *line, t_map *map, int *step, char *command)
{
	int		i;
	char	*cp;
	t_room	*a_r;
	t_room	*b_r;

	i = 0;
	a_r = NULL;
	b_r = NULL;
//	printf("test link : line = %s | line[i] = %s\n", line, line + i);
	while (1)
	{
		if (!(cp = ft_strdup(line)) || *command)
			return (cp ? 1 : -1);
		while (cp[i] && cp[i] != '-')
			i++;
//		printf("test link : line = %s | line[i] = %s\n", line, line + i);
		if (!line[i])
			return (1);
//		printf("test link\n");
		cp[i] = '\0';
		if ((a_r = find_room(cp, map)) && (b_r = find_room(cp + i + 1, map)))
			break ;
		i = line[i] ? i + 1 : i;
		free(cp);
	}
	free(cp);
	*step = 2;
	return(append_links(a_r, b_r));
}
