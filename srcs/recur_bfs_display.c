/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:14 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/19 18:56:39 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "lem_in.h"

int		compute_len(t_room *start, t_room *room, int len)
{
	t_room *current;
	
	current = room;
	while (current != start)
	{
//		printf("len\n");
		len++;
		current = current->prev;
	}
	return (len);
}

void		reset_visited(t_queue **queue)
{
	t_queue	*tmp;
	
	tmp = *queue;
	*queue = (*queue)->next;
	free(tmp);
	while (*queue)
	{
		tmp = *queue;
		(*queue)->room->visited = 0;
		*queue = (*queue)->next;
		free(tmp);
	}
}

static t_link	*find_link(t_room *room, t_room *room_dest)
{
	t_link *current_link;

	current_link = room->links;
	while (current_link)
	{
		if (current_link->room_dest == room_dest)
			return (current_link);
		current_link = current_link->next;
	}
	return (NULL);
}

static int	find_path_flow_back(t_room *room)
{
	t_link	*link;
	t_room	*current_room;
	int		nb_room;

	current_room = room;
	nb_room = 0;
	while ((link = find_flow(current_room->links, -1)))
	{
		nb_room++;
		current_room = link->room_dest;
	}
	return (nb_room);
}

static t_queue	*find_bfs_path(t_map *map)
{
	t_room	*current;
	t_queue	*path;

	current = map->end;
	path = NULL;
	if (append_start_queue(&path, current))
		return (NULL);
	while (current != map->start)
	{
		printf("path name : %s\n", current->name);
//		if (current->prev)
//			printf("prev name : %s\n", current->prev->name);
		if(append_start_queue(&path, current->prev))
			return (NULL);
		current = current->prev;
	}
	return (path);
}

static void	end_reached(t_queue **queue, int *reach_end, int nb_iter)
{
	*reach_end = 1;
	while (*queue)
	{
		(*queue)->room->visited = nb_iter;
		*queue = (*queue)->next;
	}
}

static int	normal_case(t_map *map, t_queue **queue, int nb_iter, int *reach_end)
{
	t_link	*current_link;

//	display_queue(*queue);
	printf("normal case\n");
	current_link = (*queue)->room->links;
	while (current_link)
	{
//		printf("dest : %s\n", current_link->room_dest->name);
//		printf("flow : %d\n", current_link->flow);
//		printf("visited (%d): %d\n", nb_iter, current_link->room_dest->visited);
		if (((current_link->flow == -1) || (!current_link->flow))\
				&& current_link->room_dest->visited != nb_iter) //chemin empreintable
		{
			if (verif_already_queue(queue, current_link->room_dest))
			{
				current_link = current_link->next;
				continue ;// ---> stop si deja dans la queue
			}
			if ((append_queue(queue, current_link->room_dest)))
				return (1);
			current_link->room_dest->prev = NULL;
			if (!ft_strcmp(current_link->room_dest->name, "Bei0") || !ft_strcmp(current_link->room_dest->name, "Ckk3"))
			{
				printf("prev of %s, set at %s\n", current_link->room_dest->name, (*queue)->room->name);
				printf("%s, set prev visited(%d) = %d\n",  current_link->room_dest->name, nb_iter, current_link->room_dest->visited);
				printf("%s, set prev visited(%d) = %d\n", (*queue)->room->name, nb_iter, (*queue)->room->visited);
				usleep(6294960);
			}
			current_link->room_dest->prev = (*queue)->room;
			if (current_link->room_dest == map->end)
			{
				printf("END REAACHED !!\n");
				end_reached(queue, reach_end, nb_iter);
				break ;
			}
		}
		current_link = current_link->next;
	}
//	if ((*queue)->room->prev)
//	
	if (*queue && (!ft_strcmp((*queue)->room->name, "Bei0") || !ft_strcmp((*queue)->room->name, "Ckk3")))
	{
			printf("%s, normal visited(%d) = %d\n",  (*queue)->room->name, nb_iter, (*queue)->room->visited);
			usleep(6294960);
	}
//	printf("node : %s | prev = %s\n", (*queue)->room->name, (*queue)->room->prev->name);
	if (*queue)
		*queue = (*queue)->next;
	return (0);
}

static int		case_flow_from_empty_flow(t_queue **queue, t_link *link, int nb_iter)
{
	if (link->room_dest->visited == nb_iter) // cul-de-sac = reset
	{
		*queue = (*queue)->next;
		return (1) ;
	}
	if (verif_already_queue(queue, link->room_dest))
		return (1) ;
	if ((append_queue(queue, link->room_dest)))
		return (-1);
	if (!ft_strcmp((*queue)->room->name, "Bei0") || !ft_strcmp((*queue)->room->name, "Ckk3"))
	{
		printf("other one\n");
		usleep(6294960);
	}
	link->room_dest->prev = (*queue)->room;
	if (*queue)
		printf("%s, case flow empty visited(%d) = %d\n",  (*queue)->room->name, nb_iter, (*queue)->room->visited);
	if (*queue && (!ft_strcmp((*queue)->room->name, "Bei0") || !ft_strcmp((*queue)->room->name, "Ckk3")))
	{
			printf("%s, visited(%d) = %d\n",  (*queue)->room->name, nb_iter, (*queue)->room->visited);
			usleep(6294960);
	}
	*queue = (*queue)->next; 
	return (1) ;
}

t_queue		*recur_bfs(t_map *map, t_room *room, int nb_iter, int *best_len)
{
	t_queue	*head_queue;
	t_queue	*queue;
	t_queue	*path;
	t_queue	*tmp_path;
	int		len;
	t_link	*current_link;
	t_link	*prev_link;
	int		reach_end;

	path = NULL;
	reach_end = 0;
	head_queue = NULL;
	prev_link= NULL;
	append_queue(&head_queue, room);
	queue = head_queue;
	len = find_path_flow_back(room);
	while (queue && (!best_len || compute_len(room, queue->room, len) < *best_len))
	{
//		display_queue(queue);
//		printf("len = %d\n", compute_len(room, queue->room, len));
		printf("node = %s\n", queue->room->name);
		if (best_len)
			printf("best_len  : %d\n", *best_len);
		queue->room->visited = nb_iter;
		if ((current_link = find_flow(queue->room->links, -1)))
		{
			// appel fct si flow && room_dest link -1 n'est pas visite
			if (current_link->room_dest->visited != nb_iter)
			{	
				printf("appel recur : on %s from %s\n", current_link->room_dest->name, room->name);
				usleep(1294960);
				current_link->room_dest->prev = queue->room;
				tmp_path = recur_bfs(map, current_link->room_dest, nb_iter, best_len);
				if (tmp_path)
					path = tmp_path;
			}
			// Cas classique de gestion de room avec un flux
			prev_link = find_link(queue->room, queue->room->prev);
			if (!prev_link->flow)
			{
				if (case_flow_from_empty_flow(&queue, current_link, nb_iter) == -1)
					return (NULL);
				continue ;
			}					
		}
		if ((normal_case(map, &queue, nb_iter, &reach_end)))
			return (NULL);

	}
	printf("end whle queue\n");
	if (reach_end)
	{
		printf("find\n");
		if (!(path = find_bfs_path(map)))
			return (NULL);
		printf("find2\n");
		len = compute_len(room, map->end, len);
		printf("ok path --> len = %d\n", len);
		best_len = &len;
	}
	reset_visited(&head_queue);
	// ATTENTION retrun (NULL) en cas de malloc && path non trouve
	printf("end bfs\n");
	return (path);
}

// reinitialiser visited
// incrementer len ou calculer len
