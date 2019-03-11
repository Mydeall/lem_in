/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:00:02 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/05 17:15:11 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long int n)
{
	int				len;
	long long int	cpy;
	char			*s;

	cpy = n;
	len = (cpy == 0 ? 1 : 0);
	while (cpy != 0)
	{
		cpy = cpy / 10;
		len++;
	}
	len += n < 0;
	if (!(s = ft_memalloc(len + 1)))
		return (NULL);
	s[0] = n < 0 ? '-' : '0';
	n = n < 0 ? n : -n;
	while (n != 0)
	{
		s[--len] = -(n % 10) + 48;
		n = n / 10;
	}
	return (s);
}
