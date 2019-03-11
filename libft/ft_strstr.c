/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:38:30 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/08 15:23:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int j;

	if (to_find[0] == '\0')
		return ((char*)str);
	while (*str != '\0')
	{
		j = 0;
		while (str[j] == to_find[j] && to_find[j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return ((char*)str);
		str++;
	}
	return (0);
}
