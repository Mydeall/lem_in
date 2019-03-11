/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:44:59 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/12 18:21:32 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	int				dir;

	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	dir = 1;
	if (src < dest)
	{
		s += (n - 1);
		d += (n - 1);
		dir = -1;
	}
	while ((--n + 1) > 0)
	{
		*d = (unsigned char)*s;
		d += dir;
		s += dir;
	}
	return (dest);
}
