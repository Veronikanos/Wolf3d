# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 20:20:52 by vtlostiu          #+#    #+#              #
#    Updated: 2019/07/04 18:49:57 by vtlostiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

OBJ_PATH = obj
SRC_PATH = src

SRC_N	= main.c

INC = -I ./inc -I ./lib/libft/includes/

SDL_INC		= -I ./lib/frameworks/SDL2.framework/Versions/A/Headers -F ./lib/frameworks/
SDL_FR		= -rpath ./lib/frameworks -framework SDL2

CC = gcc -g

FLAG = -Wall -Wextra -Werror -pthreads

SRC = $(addprefix ./$(SRC_PATH)/, $(SRC_N))

OBJ = $(addprefix ./$(OBJ_PATH)/, $(SRC_N:.c=.o))

.PHONY: all clean fclean re

./$(OBJ_PATH)/%.o : ./$(SRC_PATH)/%.c
	$(CC) $(INC) $(SDL_INC) -c $< -o $@

all: $(NAME)

$(NAME): objdir $(OBJ)
		@make -C ./lib/libft/
		$(CC) -o $(NAME) $(OBJ) $(INC) -L ./lib/libft/ -lft $(SDL_INC) $(SDL_FR)
		@echo "        \033[0;34m Wolf3d \033[0;35m"


objdir:
	mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ)
	@make -C ./lib/libft/ clean
	@echo "\033[37;1;41m CLEAN DONE!!!!!!!! \033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C ./lib/libft/ fclean
	@echo "\033[37;1;41m C_FCLEAN DONE_!!!!!!!! \033[0m"

re:	fclean all
