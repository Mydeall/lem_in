/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:57:25 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/15 16:02:46 by rkirszba         ###   ########.fr       */
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
					printf("----link dest = %s\n", tmp2->room_dest->name);
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

void	display_paths(t_queue **paths)
{
	int		i;
	t_queue	*current_queue;

	i = 0;
	while (paths[i])
	{
		printf("Chemin %d\n", i + 1);
		current_queue = paths[i];
		while (current_queue)
		{
			printf("%s\n", current_queue->room->name);
			current_queue = current_queue->next;
		}
		printf("\n");
		i++;
	}
}
