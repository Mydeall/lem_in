/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:29:50 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/15 12:13:46 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimchar(char const *s, int c)
{
	char	*str;
	size_t	i;

	if (!(s))
		return (NULL);
	while (*s == (char)c && *s != '\0')
		s++;
	i = ft_strlen(s);
	while (i > 0 && s[i - 1] == (char)c && *s != '\0')
		i--;
	if (!(str = ft_strnew(i + 1)))
		return (NULL);
	while (i > 0)
	{
		str[i - 1] = s[i - 1];
		i--;
	}
	str[i] = s[i];
	return (str);
}
