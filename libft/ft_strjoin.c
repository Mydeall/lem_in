/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:08:18 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/07 18:09:44 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;

	if (!(s1) || !(s2) || !(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	str = ft_strcpy(str, s1);
	str = ft_strcat((char*)str, (char*)s2);
	return (str);
}
