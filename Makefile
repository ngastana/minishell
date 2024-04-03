# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 14:58:43 by ngastana          #+#    #+#              #
#    Updated: 2024/04/03 17:09:38 by ngastana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBNAME = libft.a
SRC =	./main/minishell.c \
		./main/signals.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
READFLAG =  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
READINCLUDE = -I/Users/$(USER)/.brew/opt/readline/include

GREEN       := \033[1;32m
YELLOW      := \033[0;33m
BLUE        := \033[0;34m
CYAN        := \033[0;36m
NONE        := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBNAME)
	@echo "$(BLUE)      - Compiling $(NAME)...$(NONE)"
	@gcc $(FLAGS)   $(OBJ) $(LIBNAME) $(READFLAG)  -o $(NAME)
	@echo "$(GREEN)- Compiled -$(NONE)"

$(LIBNAME):
	@echo "$(BLUE)     - Compiling LIBFT $(LIBNAME)...$(NONE)"
	@$(MAKE) -C ./libft all

	@cp ./libft/libft.a $(LIBNAME)
	@echo "$(GREEN)- Compiled -$(NONE)"

%.o: %.c
	$(CC) $(READINCLUDE) -c $(FLAGS) $^ -o $@

clean:
	@echo "$(BLUE)     - Removing object files...$(NONE)"
	@$(MAKE) -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(BLUE)     - Removing $(NAME) And $(LIBNAME)...$(NONE)"
	@$(MAKE) -C ./libft fclean
	@rm -rf $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all bonus clean fclean re
