/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:54:56 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 18:26:32 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*new_link(t_room *room_dest)
{
	t_link	*link;

	if (!(link = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	link->flow = 0;
	link->next = NULL;
	link->room_dest = room_dest;
	return (link);
}

int		append_one_link(t_room *room, t_room *room_dest)
{
	t_link *tmp;

	tmp = room->links;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
	{
		if (!(room->links = new_link(room_dest)))
			return (1);
	}
	else
	{
		if (!(tmp->next = new_link(room_dest)))
			return (1);
	}
	return (0);
}

int		append_links(t_room *a_room, t_room *b_room)
{
	if (!a_room || !b_room)
		return (1);
	if ((append_one_link(a_room, b_room) || append_one_link(b_room, a_room)))
		return (-1);
	return (0);
}
