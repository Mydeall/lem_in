/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:36:50 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/08 18:25:50 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *s;

	if (!(s = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(s, size);
	return ((void*)s);
}
