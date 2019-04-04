/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_recur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 13:05:22 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 18:11:55 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		update_flow(t_room *a_room, t_room *b_room, char side)
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

int				test_best_repartition(t_map *map)
{
	t_path	*paths;
	int		steps;
	int		i;

	i = -1;
	if (!(paths = get_paths(map)))
		return (1);
	steps = ants_repartition(map->ants, paths);
	if (map->best_steps == -1 || map->best_steps > steps)
	{
		map->best_steps = steps;
		if (map->best_paths)
			free_path(map->best_paths);
		map->best_paths = paths;
	}
	else
		free_path(paths);
	return (0);
}

int				recur_edmonds_karp(t_map *map)
{

	if (append_param(map->start, NULL, 0))
		return (-1);
	if (find_best_paths(map, map->start))
		return (-1);
	if (!map->best_paths)
		return (1);
	printf("\nBest paths after edmonds-karp :\n");
	display_paths(map->best_paths);
	printf("finale best steps : %d\n", map->best_steps);
//	display_instructions(map, map->best_paths, map->best_steps);
	free_path(map->best_paths);
	return (0);
}
