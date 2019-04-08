/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:57:51 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/04 12:42:18 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 100

int						get_next_line(const int fd, char **line);

typedef struct			s_lst_save
{
	char				*content;
	int					fd;
	struct s_lst_save	*next;
}						t_lst_save;

#endif
