/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:59:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 18:26:07 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	first_child(void)
{
	int			i;
	char		*location;
	char		*tmp;
	int			fd[2];
	char		**str;
	t_mini		cur_mini;
	char const	*str1;

	dup2(g_mini.infile, STDIN_FILENO);
	dup2(g_mini.outfile, STDOUT_FILENO);
	close(fd[0]);
	close(g_mini.infile);
	close(fd[1]);
	i = 0;
	cur_mini = g_mini;
	str1 = ft_strdup(g_mini.token->value);
	while (cur_mini.token->next && (cur_mini.token->next->type == T_IDENTIFIER || cur_mini.token->next->type == T_LESS))
	{
		cur_mini.token = cur_mini.token->next;
		if (cur_mini.token->next && cur_mini.token->type == T_LESS)
			cur_mini.token = cur_mini.token->next;
		str1 = ft_strjoin(str1, " ");
		str1 = ft_strjoin(str1, cur_mini.token->value);
	}
	str = ft_split(str1, ' ');
	while (cur_mini.location_paths[i] != NULL)
	{
		tmp = ft_strjoin(cur_mini.location_paths[i], "/");
		location = ft_strjoin(tmp, str[0]);
		if (access(location, X_OK) == 0)
		{	
			if (execve(location, str, cur_mini.enviroment) == -1)
				printf("Error execve: %s\n", strerror(errno));
			break ;
		}
		i++;
		free (location);
		free (tmp);
		//free (str1);
		//ft_clear(str);
	}
}

void	exec(void)
{
	pid_t	pid;

	if (has_redirection(g_mini) == 0)
		return ;
 	if (ft_is_builtin(g_mini.token->value))
	{
		ft_exec_builtin(g_mini.token);
		return ;
	}
	g_mini.path = find_path(g_mini.enviroment);
	g_mini.location_paths = ft_split(g_mini.path, ':');
	pid = fork();
	if (pid == -1)
	{
		free(g_mini.path);
		free(g_mini.location_paths);
		printf("Fork failed to create a new process.");
		return ;
	}
	else if (pid == 0)
	{
		first_child();
		exit (1);
	}
	wait (NULL);
	if (g_mini.location_paths)
		free(g_mini.location_paths);
	return ;
}
