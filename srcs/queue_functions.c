/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:49 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/22 17:47:18 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		verif_already_queue(t_queue **queue, t_room *room)
{
	t_queue	*tmp;
	
	tmp = *queue;
	while (tmp)
	{
		if (tmp->room == room)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		append_queue(t_queue **queue, t_room *room)
{
	t_queue	*new;
	t_queue	*tmp;

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

int		append_start_queue(t_queue **queue, t_room *room)
{
	t_queue	*new;
	t_queue	*tmp;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (1);
	new->room = room;
	new->next = NULL;
	tmp = *queue;
	*queue = new;
	(*queue)->next = tmp;
	return (0);
}

void	free_queue(t_queue *queue)
{
	t_queue	*tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
}

int			queue_len(t_queue *queue)
{
	t_queue	*current;
	int		len;

	len = 0;
	current = queue;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}


