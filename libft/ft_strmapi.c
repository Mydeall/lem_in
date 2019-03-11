/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:22:31 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/13 13:52:42 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*d;
	size_t	i;

	if (!(s) || !(f) || !(d = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		d[i] = f(i, s[i]);
	return (d);
}
