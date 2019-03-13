/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:47:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/13 18:48:24 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		verif_ants(char *line, t_map *map, int *step, char *command)
{
	if ((map->ants = is_pos_int(line)) == -1 || *command)
		return (1);
	(*step)++;
	return (0);
}

int		verif_coord(char *line, t_room *room)
{
	while (line[i])
		i++;
	while  (i >= 0 && line[i] != ' ')
		i--;
	if ((room->y = is_pos_int(line[i + 1])) == - 1)
		return (1);
	line[i] = 0;
	while  (line[i] && line[i] != ' ')
		i--;
	if (room->x = is_pos_int(line[i + 1]) == - 1)
		return (1);
	line[i] = 0;
}

int		verif_room(char *line, t_map *map, int *step, char *command)
{
	char	**line;
	char	*name;
	int		i;
	t_room	*room;

	(void)step;
	i = 0;
	if (!line || --i < 2 || !(room = (t_room*)malloc(sizeof(t_room))))
		return(1);
	room->next = NULL;
	if (verif_coord(line, room))
		return (1);
	if (!*line || !(room->name = ft_strdup(line)) || append_room(room, map))
		return (1);
	if (*command == 1)
		map->start = room;
	else if (*command == 2)
		map->end = room;
	*command = 0;
	return (0);
}