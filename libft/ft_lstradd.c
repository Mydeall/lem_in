/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:19:39 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/13 19:19:44 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstradd(t_list **lst, t_list *new)
{
	if (!(lst))
		return ;
	if (!(*lst))
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst)->next->next = NULL;
}
