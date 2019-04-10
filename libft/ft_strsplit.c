/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:37:22 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/10 16:13:18 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_tab(char **tab, int count)
{
	while (--count >= 0)
		free(tab[count]);
	free(tab);
}

static char		**filltab(char **tab, char *str, int count, char c)
{
	size_t	i;
	int		j;

	j = -1;
	while (*str == c)
		str++;
	while (++j < count)
	{
		i = 0;
		while (str[i] != c && str[i])
			i++;
		if (!(tab[j] = ft_strsub(str, 0, i)))
		{
			free_tab(tab, count);
			return (NULL);
		}
		while (str[i] && str[i] == c)
			i++;
		str = &str[i];
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		count;

	if (!(s))
		return (NULL);
	str = (char*)s;
	count = 0;
	while (*str == c)
		str++;
	while (str && *str)
	{
		str = ft_strchr(str, c);
		while (str && *str && *str == c)
			str++;
		count++;
	}
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (count + 1))))
		return (NULL);
	tab[count] = 0;
	tab = filltab(tab, (char*)s, count, c);
	return (tab);
}
