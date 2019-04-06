# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/04/04 20:27:15 by ccepre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
NAME_VIS = visu

FLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft
SRC_PATH = ./srcs
VIS_PATH = ./visualizer
INC_PATH = ./includes

SRC_NAME = display.c\
		   main.c\
		   find_best_paths.c\
		   bfs_functions.c\
		   ants_repartition.c\
		   display_instructions.c\

COM_NAME = initialize.c\
		   parser.c\
		   param_functions.c\
		   room_functions.c\
		   links_functions.c\
		   path_functions.c\
		   queue_functions.c\
		   parser_functions.c\
		   free_functions.c\

VIS_NAME = visualizer.c\
		   visualize.c\
		   update_state.c\
		   parser_v.c\
		   initialization_utils_functions.c\
		   draw_map.c\
		   sdl_tools.c

INC_NAME = lem_in.h \
		   get_next_line.h \
		   ft_printf.h \
		   libft.h

LIB_NAME = libft.a

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
VIS = $(addprefix $(VIS_PATH)/, $(VIS_NAME))
COM = $(addprefix $(SRC_PATH)/, $(COM_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))

OBJ_SRC= $(SRC:.c=.o)
OBJ_COM= $(COM:.c=.o)
OBJ_VIS= $(VIS:.c=.o)

all : lib $(NAME) $(NAME_VIS)

%.o : %.c $(INC)
	gcc $(FLAGS) -c `~/SDL2/SDL2-2.0.8/build/sdl2-config --cflags` $< -o $@ -I $(INC_PATH)

$(NAME) : $(OBJ_SRC) $(OBJ_COM) $(INC) $(LIB_PATH)/libft.a
	@gcc -o $(NAME) $(OBJ_SRC) $(OBJ_COM) $(LIB) -I $(INC_PATH)
	@echo "lem-in has been well compiled"

# $(NAME_VIS) : $(OBJ_VIS) $(OBJ_COM) $(INC) $(LIB)
# 	@gcc -F/Library/Frameworks -framework SDL2 -o $(NAME_VIS) $(OBJ_VIS) $(OBJ_COM) $(LIB_PATH)/libft.a -I $(INC_PATH)
#	@echo "visu has been well compiled"

lib :
	@cd $(LIB_PATH) ; $(MAKE) -f Makefile

clean :
	rm -f $(OBJ_SRC) $(OBJ_VIS) $(OBJ_COM)
	cd $(LIB_PATH) ; $(MAKE) fclean 

fclean : clean
	rm -f $(NAME) $(NAME_VIS)

re : fclean all

san : $(OBJ_SRC) $(OBJ_VIS) $(OBJ_COM) $(OBJ_LIB) $(INC)
	cd $(LIB_PATH) ; $(MAKE) -f Makefile
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ_SRC) $(OBJ_COM) $(LIB) -I $(INC_PATH)
	gcc -g3 -fsanitize=address -F/Library/Frameworks -framework SDL2 -o $(NAME_VIS) $(OBJ_VIS) $(OBJ_COM) $(LIB) -I $(INC_PATH)

.PHONY : san lib visu clean fclean re

