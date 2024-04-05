# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 14:58:43 by ngastana          #+#    #+#              #
#    Updated: 2024/04/05 14:34:38 by ngastana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBNAME = libft.a
SRC =	./main/minishell.c \
		./main/signals.c \
		./exec/exec.c \
		./token/token.c \
		./token/handle_token.c \
		./token/token_utils.c \
		./token/handle_without_token.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
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
	@echo "$(BLUE)███████████████████████ Making minishell ███████████████████████$(YELLOW)"
	@gcc $(FLAGS)   $(OBJ) $(LIBNAME) $(READFLAG)  -o $(NAME)
	@echo "$(CLR_RMV)███████████████████████ Compiling is DONE ██████████████████████$(RESET)"
	@echo ""
	@echo ""
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo ""	
	@echo ""
	@echo "$(CLR_RMV)██████████████ $(CURSIVE)  Done by : \033[1;91memunoz\033[m$(CURSIVE) and \033[1;91mngastana\033[m   ███████████████"
	@echo ""

$(LIBNAME):
	@echo "$(BLUE)█████████████████████████ Making LIBFT █████████████████████████$(RESET)"
	@$(MAKE) -C ./libft all
	@cp ./libft/libft.a $(LIBNAME)

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