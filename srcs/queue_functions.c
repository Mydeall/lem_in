/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:51:49 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 16:40:00 by ccepre           ###   ########.fr       */
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

void	remove_queue_elem(t_queue **head_queue, t_queue *elem)
{
	t_queue *current;
	t_queue *prev_current;

	current = *head_queue;
	prev_current = NULL;
	while (current)
	{
		if (current == elem)
		{
			if (!prev_current)
				*head_queue = (*head_queue)->next;
			else
				prev_current->next = current->next;
			free(current);
			return ;
		}
		prev_current = current;
		current = current->next;
	}
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

//	printf("%p\n", queue);
//	display_queue(queue);
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
