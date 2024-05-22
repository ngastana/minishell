# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 14:58:43 by ngastana          #+#    #+#              #
#    Updated: 2024/05/21 21:33:19 by ngastana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBNAME = libft.a
SRC =	./main/minishell.c \
		./main/signals.c \
		./exec/exec.c \
		./exec/exec_builtin.c \
		./exec/exec_redir.c \
		./token/token.c \
		./token/handle_token.c \
		./token/token_utils.c \
		./token/handle_without_token.c \
		./parsing/parse.c \
		./parsing/parser_dolar.c \
		./parsing/parse_consecutive_token.c \
		./parsing/parse_DLESS_token.c \
		./parsing/parse_PIPE_token.c \
		./builtins/echo.c \
		./builtins/env.c \
		./builtins/pwd.c \
		./builtins/cd.c \
		./builtins/export.c \
		./builtins/export_sort.c \
		./builtins/export_utils.c \
		./builtins/unset.c \
		./cleaning.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3
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
	@echo "$(BLUE)████████████████████████ Making minishell ██████████████████████$(YELLOW)"
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
	@echo "$(BLUE)██████████████████████████ Making LIBFT ████████████████████████$(RESET)"
	@$(MAKE) -C ./libft all > /dev/null
	@cp ./libft/libft.a $(LIBNAME)

%.o: %.c
	@$(CC) $(READINCLUDE) -c $(FLAGS) $^ -o $@

clean:
	@$(MAKE) -C ./libft clean > /dev/null
	@rm -rf $(OBJ)
	@echo "$(CYAN)████████████████████████ cleaning is DONE ██████████████████████$(RESET)"

fclean: clean
	@$(MAKE) -C ./libft fclean > /dev/null
	@rm -rf $(NAME) $(LIBNAME)
	@echo "$(CYAN)███████████████████████ fcleaning is DONE  █████████████████████$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re