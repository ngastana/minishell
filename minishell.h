/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:40:54 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 21:50:21 by ngastana         ###   ########.fr       */
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
# include <stdbool.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef COLORS_H
#  define COLORS_H

#  define BOLD       "\001\033[1m\002"
#  define UNDERLINE  "\001\033[4m\002"
#  define BLACK      "\001\033[30m\002"
#  define RED        "\001\033[31m\002"
#  define GREEN      "\001\033[32m\002"
#  define YELLOW     "\001\033[33m\002"
#  define BLUE       "\001\033[34m\002"
#  define MAGENTA    "\001\033[35m\002"
#  define CYAN       "\001\033[36m\002"
#  define WHITE      "\001\033[37m\002"
#  define RESET      "\001\033[0m\002"

# endif



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
	int					quotation_mark;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_mini
{
	t_token	*token;
	t_token	*parsed;
	bool	signal_exec;
	int		infile;
	int		outfile;
	char	**enviroment;
	char	*path;
	char	**location_paths;
}	t_mini;

extern	t_mini	g_mini;

/*MAIN*/
int		main(int argc, char **argv, char **env);
int		ft_compare(const char *s1, const char *s2);

/*EXEC*/
void	exec(t_mini mini, char **env);
int		ft_exec_builtin(t_token *token, char **env);
int		ft_is_builtin(char *arg);

/*TOKENS*/
int		ft_space(char c);
char	*ft_skip_spaces(char *line);
t_token	*ft_token(char *input);
int		ft_handle_token(char **line_ptr, t_token **token_list);
int		ft_without_token(char **line, t_token **token);
int		ft_is_quote(char c);
int		ft_is_separator(char *s);
char	*ft_skip_spaces(char *line);
t_token	*ft_add_new_token(char *value, int mark, t_token_type type);
void	ft_add_token(t_token **token, t_token *new_token);
void	ft_clear_token(t_token **token);

/*PARSING*/
void	parse(t_mini mini);
void	parser_dolar(t_mini mini);
void	parse_consecutive_token(t_mini mini);
void	parse_PIPE_token(t_mini mini);
void	parse_DLESS_token(t_mini mini);

/*EXEC_BUILTIN*/
int		ft_env(char **env);
int		ft_pwd(void);
int		ft_echo (t_token *token);
int		ft_cd(t_token *current, char **env);
/*EXEC_BUINTIN_EXPORT*/
int		ft_export(t_token *token, char **env);
void	export_sort(char **export);
int 	search_export(char *str, char **export);
int		check_value(char *str);
char 	**add_to_export(char *str, char **export);
void	change_value(char *str, char **export);
void 	add_to_env(char *str, char **env, int flag);


/*SIGNALS*/
void	signal_handlers(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_eof(void);

/*CLEANING*/
void	ft_clean(t_mini mini);
void	ft_clear(char **matrix);

#endif