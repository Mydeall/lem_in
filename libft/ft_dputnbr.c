/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:13:39 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/06 14:09:16 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_dputnbr(long double n, int precision)
{
	int		count;

	if (n < 0)
	{
		n = (double)-n;
		ft_putchar('-');
	}
	count = 0;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	while (n > 0 && (precision == -1 || count > -precision))
	{
		ft_putchar((int)n + '0');
		n = (n - (int)n) * 10;
		if (!(--count + 1))
			ft_putchar('.');
	}
}
