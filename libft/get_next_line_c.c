/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:35 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/08 15:11:39 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int			save(const int fd, char *rest, t_lst_save **lst)
{
	t_lst_save	*current;
	t_lst_save	*tmp;

	current = *lst;
	while (current)
	{
		if (current->fd == (int)fd)
		{
			ft_strdel(&(current->content));
			free(current->content);
			current->content = rest;
			return (1);
		}
		current = current->next;
	}
	if (!(tmp = (t_lst_save*)malloc(sizeof(t_lst_save))))
		return (0);
	tmp->content = rest;
	tmp->fd = (int)fd;
	current = *lst;
	tmp->next = current;
	*lst = tmp;
	return (1);
}

static int			last_line(int fd, char **line, t_lst_save **lst, char **s)
{
	if (ft_strcmp(*s, "\0") != 0)
	{
		if (!(save(fd, "\0", lst)))
			return (-1);
		*line = ft_strdup(*s);
		ft_strdel(s);
		free(s);
		return (1);
	}
	ft_strdel(s);
	free(s);
	free((*lst)->content);
	free((*lst));
	free(lst);
	return (0);
}

static int			set_line(const int fd, t_lst_save **lst\
		, char **line, char **s)
{
	size_t	i;
	char	*rest;

	i = 0;
	while ((*s)[i] != 10 && (*s)[i] != 0)
		i++;
	if (!(rest = ft_strdup(&(*s)[i + 1])))
		return (-1);
	if (!(save(fd, rest, lst)))
		return (-1);
	*line = ft_strsub(*s, 0, i);
	ft_strdel(s);
	free(s);
	return (1);
}

static t_lst_save	**set_back(int fd, char **line, t_lst_save **lst, char **s)
{
	t_lst_save *current;

	*s = ft_strnew(1);
	if (!line)
		return (NULL);
	if (!(lst))
	{
		if (!(lst = (t_lst_save**)malloc(sizeof(t_lst_save*))))
			return (NULL);
		*lst = NULL;
	}
	current = *lst;
	while (current)
	{
		if (current->fd == (int)fd)
		{
			ft_strdel(s);
			*s = ft_strdup(current->content);
		}
		current = current->next;
	}
	return (lst);
}

int					get_next_line(const int fd, char **line)
{
	int					ret;
	static t_lst_save	**lst;
	char				buf[BUFF_SIZE + 1];
	char				**s;

	if (BUFF_SIZE < 1 || !(s = (char**)malloc(sizeof(char*))))
		return (-1);
	if (!(lst = set_back(fd, line, lst, s)))
		return (-1);
	if (ft_strchr(*s, 10))
		return (set_line(fd, lst, line, s));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = 0;
		*line = *s;
		*s = ft_strjoin(*s, buf);
		ft_strdel(line);
		if (ft_strchr(*s, 10))
			return (set_line(fd, lst, line, s));
	}
	if (ret == 0)
		return (last_line(fd, line, lst, s));
	return (0);
}
