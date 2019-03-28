# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/03/28 17:08:31 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
NAME_VIS = visualizer

FLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft
SRC_PATH = ./srcs
VIS_PATH = ./visualizer
INC_PATH = ./includes

SRC_NAME = free_functions.c\
		   parser.c\
		   display.c\
		   recur_bfs.c\
		   bfs_functions.c\
		   edmonds_karp_recur.c\
		   ants_repartition.c\
		   display_instructions.c 

COM_NAME = main.c\
		   room_functions.c\
		   links_functions.c\
		   queue_functions.c\
		   parser_functions.c

VIS_NAME = visualizer.c\
		   visualize.c\
		   update_state.c\
		   parser_v.c\
		   initialization_utils_functions.c\
		   draw_map.c\
		   

INC_NAME = lem_in.h \
		   get_next_line.h \
		   ft_printf.h \
		   libft.h

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
VIS = $(addprefix $(VIS_PATH)/, $(VIS_NAME))
COM = $(addprefix $(SRC_PATH)/, $(COM_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))

OBJ_SRC= $(SRC:.c=.o)
OBJ_COM= $(COM:.c=.o)
OBJ_VIS= $(VIS:.c=.o)

all : libft $(NAME) $(NAME_VIS)

%.o : %.c $(INC)
	gcc $(FLAGS) -c $< -o $@ -I $(INC_PATH) 

$(NAME) : $(OBJ_SRC) $(OBJ_COM) $(INC) $(LIB_PATH)/libft.a
	gcc -o $(NAME) $(OBJ_SRC) $(OBJ_COM) $(LIB_PATH)/libft.a -I $(INC_PATH)

$(NAME_VIS) : $(OBJ_VIS) $(OBJ_COM) $(INC) $(LIB_PATH)/libft.a
	gcc -F/Library/Frameworks -framework SDL2 -o $(NAME_VIS) $(OBJ_VIS) $(OBJ_COM) $(LIB_PATH)/libft.a -I $(INC_PATH)

libft :
	@cd $(LIB_PATH) ; $(MAKE) -f Makefile

clean :
	rm -f $(OBJ_SRC) $(OBJ_VIS) $(OBJ_COM)
	cd $(LIB_PATH) ; $(MAKE) fclean 

fclean : clean
	rm -f $(NAME) $(NAME_VIS)

re : fclean all

san : $(OBJ_SRC) $(OBJ_VIS) $(OBJ_COM) $(OBJ_LIB) $(INC)
	cd $(LIB_PATH) ; $(MAKE) -f Makefile
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ_SRC) $(OBJ_COM) $(LIB_PATH)/libft.a -I $(INC_PATH)
	gcc -F/Library/Frameworks -framework SDL2 -o $(NAME_VIS) $(OBJ_VIS) $(OBJ_COM) $(LIB_PATH)/libft.a -I $(INC_PATH)

.PHONY : san libft clean fclean re
