/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:24:51 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/08 17:29:26 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	char	*s;

	s = (char*)str;
	while ((--n + 1) > 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((void*)s);
		s++;
	}
	return (NULL);
}
