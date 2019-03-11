/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:12:09 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/13 19:12:22 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst_str(t_list *lst)
{
	ft_putstr("{\n");
	if (!(lst))
		ft_putstr("(null)\n");
	while (lst)
	{
		ft_putchar('|');
		ft_putstr(lst->content);
		ft_putchar('|');
		ft_putchar('\n');
		lst = lst->next;
	}
	ft_putstr("}\n");
}
