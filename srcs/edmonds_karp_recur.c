/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_recur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 13:05:22 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 15:53:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	update_flow(t_room *a_room, t_room *b_room, char side)
{
	t_link	*current_link;

	current_link = a_room->links;
	while (current_link)
	{
		if (current_link->room_dest == b_room)
		{
			if (current_link->flow == -1 || current_link->flow == 1)
				current_link->flow = 0;
			else
				current_link->flow = side;
			break ;
		}
		current_link = current_link->next;
	}
}

void			update_flow_path(t_queue *path, char side)
{
	t_queue *current;
	
//	printf("update flow  :\n");
//	display_queue(path);
	current = path;
	if (!path)
		return ;
	while (current->next)
	{
		update_flow(current->room, current->next->room, side);
		update_flow(current->next->room, current->room, -side);
		current = current->next;
	}
}

static t_queue	*browse_path(t_map *map, t_room *current_room)
{
	t_queue	*path;
	t_link	*link;
	
	path = NULL;
	if (append_queue(&path, map->start))
		return (NULL);
	while (current_room != map->end)
	{
		if (append_queue(&path, current_room))
			return (NULL);
		if (!(link = find_flow(current_room->links, 1)))
		{
			print_map(map);
			display_queue(path);
			display_room(current_room);
			printf("bug d'update de flow room : %s\n", current_room->name);
			return (NULL);
		}
		current_room = link->room_dest;
	}
	if (append_queue(&path, current_room))
		return(NULL);
	return (path);
}

t_path	*get_paths(t_map *map)
{
	t_link	*current_link;
	t_path	*paths;
	int		nb_paths;

	nb_paths = 0;
	current_link = map->start->links;
	while (current_link)
	{
		if (current_link->flow == 1)
			nb_paths++;
		current_link = current_link->next;
	}
	if (!(paths = (t_path*)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	paths[nb_paths].path = NULL;
	current_link = map->start->links;
	nb_paths = 0;
	while (current_link)
	{
		if (current_link->flow == 1)
		{
			if (!(paths[nb_paths].path = browse_path(map, current_link->room_dest)))
			{
				//free
				return (NULL);
			}
			paths[nb_paths].steps = 0;
			paths[nb_paths].size = 0;
			paths[nb_paths].ants = 0;
			nb_paths++;
		}
		current_link = current_link->next;
	}
	return (paths);
}

int		test_best_repartition(t_map *map, t_path **best_paths, int *best_steps)
{
	t_path	*paths;
	int		steps;
	int		i;

	i = -1;
	if (!(paths = get_paths(map)))
		return (1);
	steps = ants_repartition(map->ants, paths);
	if (*best_steps == -1 || *best_steps > steps)
	{
		*best_steps = steps;
		if (*best_paths)
		{
			while ((*best_paths)[++i].path)
				free_queue((*best_paths)[i].path);
			free(*best_paths);
		}
		*best_paths = paths;
	}
	else
	{
		while (paths[++i].path)
			free_queue(paths[i].path);
		free(paths);
	}
	return (0);
}
	

void	reverse_paths(t_path *paths)
{
	int j;
	int k;
	t_queue *current_i;
	t_queue *current_j;
	t_room	*tmp;

	while (paths && (*paths).path)
	{
		j = queue_len((*paths).path);
		current_i = (*paths).path;
		while (j > queue_len((*paths).path)/2)
		{
			current_j = (*paths).path;
			k = -1;
			while (++k < j - 1)
				current_j = current_j->next;
			tmp = current_i->room;
			current_i->room = current_j->room;
			current_j->room = tmp;
			j--;
			current_i = current_i->next;
		}	
		paths++;
	}
}

int		edmond_retour(t_map *map, t_path **best_paths, int *best_steps)
{
	t_path	*tmp_paths;
	int		tmp_steps;
	t_room	*tmp;

	tmp_steps = -1;
	tmp_paths = NULL;
	tmp = map->start;
	map->start = map->end;
	map->end = tmp;
	if (append_param(map->start, NULL, 0))
		return (1);
	if (recur_bfs(map, map->start, &tmp_steps, &tmp_paths))
		return (1);
	if (tmp_steps < *best_steps || !*best_paths)
	{
		*best_steps = tmp_steps;
		reverse_paths(tmp_paths);
		*best_paths = tmp_paths;
		printf("best_retour\n");
	}
	tmp = map->start;
	map->start = map->end;
	map->end = tmp;
	return (0);
}

int	edmond_best_len(t_map *map, t_path **best_paths, int *best_steps)
{
	int 	steps;
	int 	best_len;
	t_queue	*best_bfs_path;
	t_path	*paths;

	while (1) //gerer 1 pour malloc
	{
		best_len = -1;
		best_bfs_path = NULL;
		if (append_param(map->start, NULL, 0))
			return (1);
		if (bfs_best_len(map, map->start, &best_len, &best_bfs_path))
			return (1);
		if (!best_bfs_path)
			break ;
		if (!(paths = get_paths(map)))
			return (1);
		display_paths(paths);
		usleep(5000000);
		update_flow_path(best_bfs_path, 1);
	}
	if (test_best_repartition(map, &paths, &steps))
		return (1);
	if (steps < *best_steps || !*best_paths)
	{
		*best_paths = paths;
		*best_steps = steps;
		printf("best_len\n");
	}
	return (0);
}

int		recur_edmonds_karp(t_map *map)
{
	t_path	*best_paths;
	int		best_steps;

	best_steps = -1;
	best_paths = NULL;
	if (append_param(map->start, NULL, 0))
		return (1);
	if (recur_bfs(map, map->start, &best_steps, &best_paths))
		return (1);
//	if (edmond_retour(map, &best_paths, &best_steps))
//		return (1);
//	if (edmond_best_len(map, &best_paths, &best_steps))
//		return (1);
	if (!best_paths) //la fin n'a pas ete atteinte
		return (1);
//	printf("\nBest paths after edmonds-karp :\n");
//	display_paths(best_paths);
//	printf("finale best steps : %d\n", best_steps);
	display_instructions(map, best_paths, best_steps);
	return (0);
}
