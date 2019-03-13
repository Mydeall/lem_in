/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:06:13 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/13 19:12:51 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"

# define HASH_SIZE 9679

struct s_link;

typedef struct	s_room
{
	char			*name;
	struct s_link	*links;
	int				x;
	int				y;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	t_room			*room_dest;
	char			flow;
	struct s_link	*next;
	
}				t_link;

typedef struct	s_map
{
	int				ants;
	t_room			*start;
	t_room			*end;
	t_room			**hash_tab;
}				t_map;

typedef struct	s_tab_parser
{
	int				step;
	int				(*f)(char*, t_map*, int*, char*);
}				t_tab_parser;

int				is_pos_int(char *str);
int				verif_com(char *line, t_map *map, int *step, char *command);
int				verif_ants(char *line, t_map *map, int *step, char *command);
int				verif_room(char *line, t_map *map, int *step, char *command);
int				verif_link(char *line, t_map *map, int *step, char *command);

#endif
