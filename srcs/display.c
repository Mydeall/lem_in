/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:57:25 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/03 17:46:54 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_map(t_map *map)
{
	int		i;
	t_room	*tmp;
	t_link	*tmp2;
	int count_rooms;
	int count_links;

	count_rooms = 0;
	count_links = 0;
	i = 0;
	printf("ants = %d\n", map->ants);
	if (map->start)
		printf("start = %s\n", map->start->name);
	else
		printf("start = %p\n", map->start);
	if (map->end)
		printf("end = %s\n", map->end->name);
	else
		printf("end = %p\n", map->end);
	while (i < HASH_SIZE)
	{
		if (map->hash_tab[i])
		{
			tmp = map->hash_tab[i];
			printf("---- CELLULE ----\n");
			while (tmp)
			{
				count_rooms++;
				printf("room name = %s\n", tmp->name);
				tmp2 = tmp->links;
				if (!tmp2)
					printf("----link dest = %p\n", tmp2);
				while (tmp2)
				{
					count_links++;
					printf("----link dest = %s | flow = %d\n", tmp2->room_dest->name, tmp2->flow);
					tmp2 = tmp2->next;
				}
				tmp = tmp->next;
				if (tmp)
					printf("OK COLLISION : %p\n", tmp);
			}
			printf("--------------\n");
		}
		i++;
	}
	printf("nb_rooms : %d\nnb_links : %d\n", count_rooms, count_links);
}

void	display_paths(t_path *paths)
{
	int		i;
	//	t_queue	*path;

	i = 0;
//	printf("DISPLAY\n");
	if (!paths)
	{
		printf("%p\n", NULL);
		return ;
	}
	while (paths[i].path)
	{
		printf("Chemin %d\n", i + 1);
		//		path = paths[i]->path;
//		printf("size : %d\nants : %d\nsteps : %d\n", paths[i].size,\
//				paths[i].ants, paths[i].steps);
		display_queue(paths[i].path);
		//		while (path)
		//		{
		//			printf("%s", path->room->name);
		//			if (path->next)
		//				printf("->");
		//			path = path->next;
		//		}
		i++;
		printf("\n");
	}
}

void	display_queue(t_queue *queue)
{
	t_queue	*current_queue;

	printf("queue :\n");
	current_queue = queue;
	while (current_queue)
	{
		printf("%s", current_queue->room->name);
		if (current_queue->next)
			printf("->");
		current_queue = current_queue->next;
	}
	printf("\n");
}

void	display_room(t_room *room)
{
	t_link *current;

	printf("----- display room -----\n");
	printf("room name = %s\n", room->name);
	current = room->links;
	if (!current)
		printf("----link dest = %p\n", current);
	while (current)
	{
		printf("----link dest = %s | flow = %d\n",
				current->room_dest->name, current->flow);
		current = current->next;
	}
	printf("-----------------------\n");
}
