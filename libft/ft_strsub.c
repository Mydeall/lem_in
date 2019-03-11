/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:02:33 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/03 17:54:10 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!(s) || !(str = ft_strnew(len + 1)))
		return (NULL);
	i = 0;
	while ((--len + 1) > 0)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
