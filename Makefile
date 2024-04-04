# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 14:58:43 by ngastana          #+#    #+#              #
#    Updated: 2024/04/04 16:56:16 by ngastana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBNAME = libft.a
SRC =	./main/minishell.c \
		./main/signals.c \
		./exec/exec.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
READFLAG =  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
READINCLUDE = -I/Users/$(USER)/.brew/opt/readline/include

.SILENT:

CLR_RMV     := \033[0m
GREEN       := \033[1;32m
YELLOW      := \033[0;33m
BLUE        := \033[0;34m
CYAN        := \033[0;36m
CURSIVE		:= \033[3m

all: $(NAME)

$(NAME): $(OBJ) $(LIBNAME)
	@gcc $(FLAGS)   $(OBJ) $(LIBNAME) $(READFLAG)  -o $(NAME)
	@echo "\n$(GREEN) $(CURSIVE) 🆒 COMPILED MINISHELL 🆒 \n"

$(LIBNAME):
	@$(MAKE) -C ./libft all
	@cp ./libft/libft.a $(LIBNAME)
	@echo "$(YELLOW) $(CURSIVE)"

%.o: %.c
	@$(CC) $(READINCLUDE) -c $(FLAGS) $^ -o $@

clean:
	@$(MAKE) -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) -C ./libft fclean
	@rm -rf $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all bonus clean fclean re
