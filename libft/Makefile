# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/03/28 17:24:30 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

LIB_PATH = .
PRINTF_PATH = ./ft_printf
INC_PATH = ./../includes

LIB_NAME = ft_strcpy.c\
		   ft_strdel.c\
		   ft_atoi.c\
		   ft_strdup.c\
		   ft_strsub.c\
		   ft_strcat.c\
		   ft_strchr.c\
		   ft_strjoin.c\
		   ft_strjoinarg.c\
		   ft_strnew.c\
		   ft_strcmp.c\
		   ft_strlen.c\
		   ft_bzero.c\
		   ft_memalloc.c\
		   ft_memset.c\
		   ft_itoa_base.c\
		   ft_pow.c \
		   ft_strsplit.c \
		   ft_isdigit.c \
		   ft_putstrtab.c \
		   ft_putstr.c \
		   ft_putchar.c \
		   ft_putendl.c \
		   ft_putinttab.c \
		   ft_putnbr.c \
		   ft_itoa.c \
		   ft_strjointab.c \
		   ft_abs.c \
		   ft_strstr.c \
		   ft_memcpy.c \
		   ft_putlst_str.c \
		   ft_freetab.c \
		   ft_dtoa.c \
		   ft_strtrimchar.c \
		   ft_strsplitstr.c \
		   ft_strncmp.c \
		   get_next_line.c

PRINTF_NAME = ft_printf.c \
		   lst_functions.c \
		   ft_stack_applier.c \
		   ft_format.c \
		   ft_modifier.c \
		   ft_conversion.c \
		   ft_precision.c \
		   ft_attributs.c \
		   ft_width.c \
		   ft_parser.c \
		   ft_struct_fct.c

INC_NAME = ft_printf.h \
		   libft.h \
		   get_next_line.h

LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
PRINTF = $(addprefix $(PRINTF_PATH)/, $(PRINTF_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))

HEADERS = ./../includes

OBJS_LIB = $(LIB:.c=.o)
OBJS_PRINTF = $(PRINTF:.c=.o)

all : $(NAME)

%.o : %.c
	@gcc $(FLAGS) -c $< -o $@ -I $(HEADERS)

.PHONY : clean fclean re

$(NAME) : $(OBJS_LIB) $(OBJS_PRINTF) $(INC)
	@ar rc $(NAME) $(OBJS_LIB) $(OBJS_PRINTF)
	@ranlib $(NAME)
	@echo "Libft has been well compiled"

clean :
	rm -f $(OBJS_LIB) $(OBJS_PRINTF)

fclean : clean
	rm -f $(NAME)

re : fclean all
