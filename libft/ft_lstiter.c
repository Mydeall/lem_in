/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:48:21 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/17 12:16:30 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *ielem))
{
	t_list *cpy;

	if (!(lst))
		return ;
	cpy = lst;
	while (cpy != NULL)
	{
		f(cpy);
		cpy = cpy->next;
	}
}
