# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 09:03:02 by amanjon-          #+#    #+#              #
#    Updated: 2024/01/03 08:07:58 by amanjon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
#DEBUG = -g3 -fsanitize=address
#DEBUG = -g3 -fsanitize=thread
RM = rm -f
SRC = philo.c init_table.c cycle_threads.c routine.c utils.c
#SRC = sandbox.c 

SRC_DIR = ./src/
OBJ_DIR = ./obj/

OBJ_FILES = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# COLOURS
GREEN = \033[0;32m
COLOR_OFF = \033[0m

# RULES
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# basic library compiled
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) -o $(NAME)
	@echo "$(GREEN)#### philo ####$(COLOR_OFF)"
	@echo "    -Has been compiled ✅"

# all .o files removed
clean:
	@$(RM) $(OBJ)
	@rm -rf $(OBJ_DIR)

# library .a file removed
fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(OBJ_DIR)

re:	fclean all

.PHONY:	all clean fclean re