/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:06:13 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/20 16:03:41 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>

# define HASH_SIZE 9679

struct s_link;

typedef struct	s_room
{
	char			*name;
	struct s_link	*links;
	int				x;
	int				y;
	struct s_room	*next;
	struct s_room	*prev;
	int				visited;
	int				lock;
}				t_room;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

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

/*
** check functions
*/

void			parser(t_map *map, t_tab_parser *tab_parser, char *line);
int				is_pos_int(char *str);
int				verif_com(char *line, t_map *map, int *step, char *command);
int				verif_ants(char *line, t_map *map, int *step, char *command);
int				verif_room(char *line, t_map *map, int *step, char *command);
int				verif_link(char *line, t_map *map, int *step, char *command);

t_room			*find_room(char *name, t_map *map);
int				append_room(t_room *room, t_map *map);
int				hash_jenkins(char *name);
int				append_one_link(t_room *room, t_room *room_dest);
int				append_links(t_room *a_room, t_room *b_room);
t_link			*new_link(t_room *room_dest);

void			free_hash_tab(t_map *map);
void			free_links(t_link *link);

void			refresh_queue(t_queue **queue);
int				append_queue(t_queue **queue, t_room *room);
int				append_start_queue(t_queue **queue, t_room *room);

int				bfs(t_map *map, int nb_iter);
t_link			*find_flow(t_link *links, int value);

int				edmonds_karp(t_map *map);

void			display_paths(t_queue **paths);
void			print_map(t_map *map);
void			display_queue(t_queue *queue);
int				verif_already_queue(t_queue **queue, t_room *room);

int				recur_edmonds_karp(t_map *map);
t_queue			*recur_bfs(t_map *map, t_room *room, int *best_len);

int				compute_len(t_room *start, t_room *room, int len);
void			reset_visited(t_queue **queue);
t_link			*find_link(t_room *room, t_room *room_dest);
int				find_path_flow_back(t_room *room);
t_queue			*find_bfs_path(t_map *map);
#endif
