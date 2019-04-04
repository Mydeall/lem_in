/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:46:46 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/04 16:34:22 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_tab(char **tab, int count)
{
	while (--count >= 0)
		free(tab[count]);
	free(tab);
}

static char		**filltab(char **tab, char *str, int count, char *c)
{
	size_t	i;
	int		j;
	int		len;

	j = -1;
	len = ft_strlen(c);
	while (!ft_strncmp(str, c, len))
		str += len;
	while (++j < count)
	{
		i = 0;
		while (str[i] && ft_strncmp(str + i, c, len))
			i++;
		if (!(tab[j] = ft_strsub(str, 0, i)))
		{
			free_tab(tab, count);
			return (NULL);
		}
		while (*str && !ft_strncmp(str + i, c, len))
			i += len;
		str = &str[i];
	}
	return (tab);
}

char			**ft_strsplitstr(char const *s, char *c)
{
	char	**tab;
	char	*str;
	int		count;
	int		len;

	if (!(s))
		return (NULL);
	str = (char*)s;
	count = 0;
	len = ft_strlen(c);
	while (!ft_strncmp(str, c, len))
		str += len;
	while (str && *str)
	{
		str = ft_strstr(str, c);
		while (str && *str && !ft_strncmp(str, c, len))
			str += len;
		count++;
	}
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (count + 1))))
		return (NULL);
	tab[count] = 0;
	tab = filltab(tab, (char*)s, count, c);
	return (tab);
}
