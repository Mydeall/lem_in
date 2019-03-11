/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:37:52 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/13 14:55:31 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t j;
	size_t i;

	if (to_find[0] == '\0')
		return ((char*)str);
	i = -1;
	while (++i < n && *str != 0)
	{
		j = 0;
		while (str[j] == to_find[j] && to_find[j] != '\0' && i + j < n)
			j++;
		if (to_find[j] == '\0' && j > 0)
			return ((char*)str);
		str++;
	}
	return (0);
}
