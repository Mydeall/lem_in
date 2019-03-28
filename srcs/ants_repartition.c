/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_repartition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:08:40 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/27 17:48:38 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	sort_paths(t_path *paths, int nb_paths)
{
	t_path tmp;
	int i;
	int j;

	i = -1;
	while (++i < nb_paths)
	{
		j = 0;
		while (j < nb_paths - 1)
		{
			if (paths[j].size < paths[j + 1].size)
			{
				tmp = paths[j];
				paths[j] = paths[j + 1];
				paths[j + 1] = tmp;
				continue ;
			}
			j++;
		}
	}
}

static int	compute_ants(t_path *path, int nb_paths, int paths_len, int ants)
{
	int		ants_path;

	ants_path = (paths_len - nb_paths * path->size + ants) / nb_paths;
	return (ants_path);
}

static void	complete(t_path *paths, int ants_left)
{
	int	min_step;
	int min_index;
	int i;

	while (ants_left)
	{
		min_step = -1;
		i = -1;
		while (paths[++i].path)
		{
			if (paths[i].steps < min_step || min_step == -1)
			{
				min_step = paths[i].steps;
				min_index = i;
			}
		}
		paths[min_index].ants += 1;
		paths[min_index].steps = paths[min_index].size + paths[min_index].ants - 1;
		ants_left--;
	}
}

static int	compute_total_steps(t_path *paths)
{
	int		max_step;
	int		i;

	max_step = -1;
	i = -1;
	while (paths[++i].path)
		if (paths[i].steps > max_step || max_step == -1)
			max_step = paths[i].steps;
	return (max_step);
}

/*
 *		tmp = current->prev;
		current->prev = current->prev->next;
		current = tmp->room;
		free(tmp);
		
		current = current->prev->room;

*/

int			ants_repartition(int ants, t_path *paths)
{
	t_path	*current_path;
	int		i;
	int		nb_path;
	int		paths_len;
	int		ants_left;
	int		nb_skip;

	nb_path = -1;
	paths_len = 0;
	while (paths[++nb_path].path)
	{
		paths[nb_path].size = queue_len(paths[nb_path].path) - 1;
		paths_len += paths[nb_path].size;
	}
//	printf("nb_paths : %d\n", nb_path);
	sort_paths(paths, nb_path);
	current_path = paths;
	ants_left = ants;
	nb_skip = 0;
	i = -1;
	while (current_path[++i].path)
	{
		current_path[i].ants = compute_ants(&current_path[i], nb_path, paths_len, ants);
		if (current_path[i].ants <= 0)
		{
			paths_len -= current_path[i].size;
			current_path[i].ants = 0;
			nb_path--;
			nb_skip++;
//			printf("skip size : %d\n", current_path[i].size);
			continue ;
		}
		current_path[i].steps = current_path[i].size + current_path[i].ants - 1;
		ants_left -= current_path[i].ants;
	}
	complete(&paths[nb_skip], ants_left);
	return (compute_total_steps(&paths[nb_skip]));
}
		
