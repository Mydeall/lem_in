/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:49 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/15 18:10:13 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	refresh_queue(t_queue **queue, t_queue **prev_queue)
{
	t_queue	*tmp;

	if (!queue || !*queue)
		return ;
	tmp = *prev_queue;
	*prev_queue = (*queue);
	*queue = (*queue)->next;
//	if (tmp)
//		free(tmp);
}

int		append_queue(t_queue **queue, t_room *room)
{
	t_queue	*new;
	t_queue	*tmp;

	tmp = *queue;
	while (tmp)
	{
		if (tmp->room == room)
			return (0);
		tmp = tmp->next;
	}
	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (1);
	new->room = room;
	new->next = NULL;
	tmp = *queue;
	if (!tmp)
	{
		*queue = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
