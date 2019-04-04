/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:44:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/04 16:00:26 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

void			param_next(t_param **params)
{
	t_param	*tmp;

	if (!params || !*params)
		return ;
	tmp = *params;
	*params = (*params)->next;
	free(tmp);
}

int				append_param(t_room *room, t_room *prev, int depth)
{
	t_param	*new;

	if (!(new = (t_param*)malloc(sizeof(t_param))))
		return (1);
	new->depth = depth;
	new->prev = prev;
	new->next = room->params;
	room->params = new;
	return (0);
}


