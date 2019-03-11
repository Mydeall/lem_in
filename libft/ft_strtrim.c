/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:17 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/13 14:05:20 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;

	if (!(s))
		return (NULL);
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s != '\0')
		s++;
	i = ft_strlen(s);
	while ((s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t') \
			&& *s != '\0')
		i--;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while ((--i + 1) > 0)
		str[i] = s[i];
	return (str);
}
