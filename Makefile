# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/03/15 14:59:09 by ccepre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft
SRC_PATH = ./srcs
INC_PATH = ./includes

SRC_NAME = free_functions.c\
		   links_functions.c\
		   main.c\
		   parser.c\
		   parser_functions.c\
		   room_functions.c\
		   bfs.c \
		   edmonds_karp.c \
		   queue_functions.c

INC_NAME = lem_in.h \
		   get_next_line.h \
		   ft_printf.h \
		   libft.h

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))

OBJ_SRC= $(SRC:.c=.o)

all : libft $(NAME)

%.o : %.c $(INC)
	gcc $(FLAGS) -c $< -o $@ -I $(INC_PATH) 

$(NAME) : $(OBJ_SRC) $(OBJ_SRC_CHECK) $(INC) $(LIB_PATH)/libft.a
	gcc -o $(NAME) $(OBJ_SRC) $(LIB_PATH)/libft.a -I $(INC_PATH)

libft :
	@cd $(LIB_PATH) ; $(MAKE) -f Makefile

clean :
	rm -f $(OBJ_SRC)
	cd $(LIB_PATH) ; $(MAKE) fclean 

fclean : clean
	rm -f $(NAME)

re : fclean all

san : $(OBJ_SRC) $(OBJ_SRC_CHECK) $(OBJ_LIB) $(INC)
	cd $(LIB_PATH) ; $(MAKE) -f Makefile
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ_SRC) $(LIB_PATH)/libft.a -I $(INC_PATH)

.PHONY : san libft clean fclean re
