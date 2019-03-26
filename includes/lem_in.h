/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:06:13 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/26 14:36:42 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <time.h>

# define HASH_SIZE 9679

struct s_link;
struct s_queue;

typedef struct	s_room
{
	char			*name;
	struct s_link	*links;
	int				x;
	int				y;
	struct s_room	*next;
	struct s_queue	*prev;
	int				visited;
	int				lock;
	int				prev_depth;
	int				nb_recur;
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

typedef struct	s_path
{
	t_queue	*path;
	int		size;
	int		ants;
	int		steps;
}				t_path;

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
void			free_queue(t_queue *queue);

int				bfs(t_map *map, int nb_iter);
t_link			*find_flow(t_link *links, int value);

int				edmonds_karp(t_map *map);

void			display_paths(t_path *paths);
void			print_map(t_map *map);
void			display_queue(t_queue *queue);
int				verif_already_queue(t_queue **queue, t_room *room);

int				recur_edmonds_karp(t_map *map);
void			update_flow_path(t_queue *path, char side);
t_path			*get_paths(t_map *map);
int				test_best_repartition(t_map *map, t_path **best_paths, int *best_steps);


int				recur_bfs(t_map *map, t_room *room_start, int *best_steps,\
					t_path **best_ed_paths);
void			reset_visited(t_map *map, t_queue **queue);
t_link			*find_link(t_room *room, t_room *room_dest);
t_queue			*find_bfs_path(t_map *map);
//int			compute_len(t_room *start, t_room *room, int len);
//int			find_path_flow_back(t_room *room);

int				ants_repartition(int ants, t_path *paths);
int				queue_len(t_queue *queue);

#endif
