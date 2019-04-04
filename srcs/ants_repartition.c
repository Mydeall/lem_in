/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_repartition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:08:40 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 19:01:36 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	sort_paths(t_path *paths, int nb_paths)
{
	t_path	tmp;
	int		i;
	int		j;

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
		paths[min_index].steps = paths[min_index].size\
								+ paths[min_index].ants - 1;
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

int			sort_and_compute_paths(t_path *paths, int *paths_len)
{
	int		nb_path;

	*paths_len = 0;
	nb_path = -1;
	while (paths[++nb_path].path)
	{
		paths[nb_path].size = queue_len(paths[nb_path].path) - 1;
		*paths_len += paths[nb_path].size;
	}
	sort_paths(paths, nb_path);
	return (nb_path);
}

int			ants_repartition(int ants, t_path *paths)
{
	int		i;
	int		paths_len;
	int		ants_left;
	int		nb_path;

	ants_left = ants;
	nb_path = sort_and_compute_paths(paths, &paths_len);
	i = -1;
	while (paths[++i].path)
	{
		paths[i].ants = (paths_len - nb_path * paths[i].size + ants) / nb_path;
		if (paths[i].ants <= 0)
		{
			paths_len -= paths[i].size;
			nb_path--;
			paths++;
			i--;
			paths[i].ants = 0;
			continue ;
		}
		paths[i].steps = paths[i].size + paths[i].ants - 1;
		ants_left -= paths[i].ants;
	}
	complete(paths, ants_left);
	return (compute_total_steps(paths));
}
