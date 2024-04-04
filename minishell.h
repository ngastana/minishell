/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:40:54 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/04 15:45:40 by ngastana         ###   ########.fr       */
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

typedef struct s_mini
{
	t_in	*in;
	char	*path;
	char	**location_paths;	
}	t_mini;

/*MAIN*/
int		main(int argc, char **argv, char **env);
void	ft_signals(t_mini mini);

/*EXEC*/
void	exec(t_mini mini, char **env);

#endif