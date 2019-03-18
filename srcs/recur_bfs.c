/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/18 18:33:39 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	find_path_flow_back(t_room *room)
{
	t_link	*link;
	t_room	*current_room;
	int		nb_room;

	while ((link = find_flow(current_room->links, -1)))
	{
		nb_room++;
		current_room = link->room_dest;
	}
	return (nb_room);
}

static void	end_reached(t_queue **queue, int *reach_end, int nb_iter)
{
	*reach_end = 1;
	while (*queue)
	{
		(*queue)->room->visited = nb_iter;
		refresh_queue(queue);
	}
}

static int	normal_case(t_map *map, t_queue **queue, int nb_iter, int *reach_end)
{
	t_link	*current_link;

	current_link = (*queue)->room->links;
	while (current_link)
	{
		if (((current_link->flow == -1) || (!current_link->flow))\
				&& current_link->room_dest->visited != nb_iter) //chemin empreintable
		{
			if (verif_already_queue(queue, current_link->room_dest))
				continue ;// ---> stop si deja dans la queue
			if ((append_queue(queue, current_link->room_dest)))
				return (1);
			current_link->room_dest->prev = (*queue)->room;
			if (current_link->room_dest == map->end)
			{
				end_reached(queue, reach_end, nb_iter);
				break ;
			}
		}
		current_link = current_link->next;
	}
	if (queue)
		refresh_queue(&queue);
	return (0);
}

static int		case_flow_from_empty_flow(t_queue **queue, t_link *link, int nb_iter)
{
	if (link->room_dest->visited == nb_iter) // cul-de-sac = reset
	{
		(*queue)->room->visited = 0;
		refresh_queue(queue);
		return (1) ;
	}
	if (verif_already_queue(queue, link->room_dest))
		return (1) ;
	if ((append_queue(queue, link->room_dest)))
		return (-1);
	link->room_dest->prev = (*queue)->room;
	refresh_queue(queue);
	return (1) ;
}

int		recur_bfs(t_map *map, t_room *room, int nb_iter, t_queue **path)
{
	t_queue	*queue;
	t_queue	*tmp_path;
	t_queue	*best_path;
	int		len;
	int		best_len;
	int		tmp_len;
	t_link	*current_link;
	t_link	*prev_link;
	int		reach_end;

	reach_end = 0;
	queue = NULL;
	prev_link= NULL;
	append_queue(&queue, room);
	while (queue)
	{
		queue->room->visited = nb_iter;
		if ((current_link = find_flow(queue->room->links, -1)))
		{
			if (current_link->room_dest->visited != nb_iter)
				if (recur_bfs(map, current_link->room_dest, nb_iter, best_len);
			prev_link = find_link(queue->room, queue->room->prev);
			if (!prev_link->flow)
			{
				if (case_flow_from_empty_flow(&queue, prev_link, nb_iter) == -1)
					return (-1);
				continue ;
			}					
		}
		if ((normal_case(map, &queue, nb_iter, &reach_end)))
			return (-1);
	}
	return (reach_end);
}
