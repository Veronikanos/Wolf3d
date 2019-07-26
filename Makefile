# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 20:20:52 by vtlostiu          #+#    #+#              #
#    Updated: 2019/07/26 22:27:38 by vtlostiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

OBJ_PATH	=	obj
SRC_PATH	=	src
LIB_PATH	=	lib/libft

SRC_N		=	main.c \
				color.c \
				draw.c \
				error_handler.c \
				event_handler.c \
				get_next_line.c \
				init.c \
				list_born2die.c \
				parse_map.c \
				raycasting.c \
				validation.c

INC 		=	-I inc \
				-I $(LIB_PATH)

SDL_INC		=	-I lib/frameworks/SDL2.framework/Headers \
				-I lib/frameworks/SDL2_image.framework/Headers


SDL_FR		=	-rpath lib/frameworks \
				-F lib/frameworks \
				-framework SDL2 \
				-framework SDL2_image

CC = gcc

FLAG = -Wall -Wextra -Werror

SRC = $(addprefix src/, $(SRC_N))

OBJ = $(addprefix obj/, $(SRC_N:.c=.o))

./$(OBJ_PATH)/%.o : ./$(SRC_PATH)/%.c
	$(CC) $(INC)  $(FLAG) $(SDL_INC) -c $< -o $@

all: $(NAME)

$(NAME): objdir $(OBJ)
		make -C lib/libft/
		$(CC) -o $(NAME) $(OBJ) $(INC) -L $(LIB_PATH) -lft $(SDL_INC) $(SDL_FR)
		@echo "        \033[0;34m Wolf3d \033[0;35m"

objdir:
	mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ)
	@make -C $(LIB_PATH) clean
	@echo "\033[37;1;41m CLEAN DONE!!!!!!!! \033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "\033[37;1;41m C_FCLEAN DONE_!!!!!!!! \033[0m"

re:	fclean all

.PHONY: all clean fclean re
