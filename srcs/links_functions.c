/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:54:56 by rkirszba          #+#    #+#             */
/*   Updated: 2019/03/13 17:55:20 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*new_link(t_room *room_dest)
{
	t_link	*link;

	if (!(link = (t_link*)malloc(sizeof(t_link))))
		return (1);
	link->flow = 0;
	link->next = NULL;
	link->room_dest = room_dest;
	return (link);
}

int		append_link(t_room *room, t_room *room_dest)
{
	t_link *tmp;

	if (!room || !room_dest)
		return (1);
	tmp = room->links;
	while (tmp->next)
		tmp = tmp->next;
	if (!tmp)
	{
		if (!(room->links = new_link(room_dest)))
			return (1);
	}
	else	
		if (!(tmp->next = new_link(room_dest)))
			return (1);
	return (0);
}