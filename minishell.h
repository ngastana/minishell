/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:40:54 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/08 12:49:12 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_in
{
	char				*content;
	struct s_in			*next;
}						t_in;

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_mini
{
	t_token	*token;
	t_token	*parsed;
	char	**enviroment;
	char	*path;
	char	**location_paths;
}	t_mini;

/*MAIN*/
int		main(int argc, char **argv, char **env);
void	ft_signals(t_mini mini);

/*EXEC*/
void	exec(t_mini mini, char **env);

/*TOKENS*/
int		ft_space(char c);
char	*ft_skip_spaces(char *line);
t_token	*ft_token(char *input);
int		ft_handle_token(char **line_ptr, t_token **token_list);
int		ft_without_token(char **line, t_token **token);
int		ft_is_quote(char c);
int		ft_is_separator(char *s);
char	*ft_skip_spaces(char *line);
t_token	*ft_add_new_token(char *value, t_token_type type);
void	ft_add_token(t_token **token, t_token *new_token);
void	ft_clear_token(t_token **token);

/*PARSING*/
void	parser_dolar(t_mini mini);

#endif