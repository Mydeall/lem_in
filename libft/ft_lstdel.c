/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:24:10 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/17 12:17:43 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*lstn;

	if (!(alst))
		return ;
	lst = *alst;
	while (lst != NULL)
	{
		lstn = lst->next;
		del((lst)->content, (lst)->content_size);
		free(lst);
		lst = lstn;
	}
	free(lst);
	free(lstn);
	*alst = NULL;
}
