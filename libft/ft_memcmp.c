/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:56:11 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/12 18:22:24 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	while ((--n + 1) > 0)
	{
		c1 = *(unsigned char*)str1;
		c2 = *(unsigned char*)str2;
		if (c1 != c2)
			return (c1 - c2);
		str1++;
		str2++;
	}
	return (0);
}
