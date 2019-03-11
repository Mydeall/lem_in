/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:48:01 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/12 18:20:53 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, \
		size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
		{
			d[i] = (unsigned char)s[i];
			return (dst + i + 1);
		}
		d[i] = (unsigned char)s[i];
		i++;
	}
	return (NULL);
}
