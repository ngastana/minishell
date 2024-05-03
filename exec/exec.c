/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:59:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/03 18:35:40 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	first_child(t_mini mini, char **env)
{
	int			i;
	char		*location;
	char		*tmp;
	char *const	*str;

	i = 0;
	str = &mini.token->value;
	while (mini.location_paths[i] != NULL)
	{
		tmp = ft_strjoin(mini.location_paths[i], "/");
		location = ft_strjoin(tmp, mini.token->value);
		if (access(location, X_OK) == 0)
		{
			if (execve(location, str, env) == -1)
				printf("Error execve: %s\n", strerror(errno));
			break ;
		}
		i++;
		free (location);
		free (tmp);
	}
}

static int has_redirection(t_mini mini)
{
	t_token	*current_token;

	current_token = mini.token;
	while (current_token)
	{
		if (current_token->type == T_GREAT && current_token->next)
		{
			mini.outfile = open(current_token->next->value, O_TRUNC | O_CREAT | O_RDWR, 0777);
			if (mini.outfile < 0)
				return (printf("Error outfile: %s\n", strerror(errno)), 0);
			dup2(mini.outfile, STDOUT_FILENO);	
		}
		else if (current_token->type == T_DGREAT && current_token->next)
		{
			mini.outfile = open(current_token->next->value, O_CREAT | O_RDWR, 0777);
			if (mini.outfile < 0)
				return (printf("Error outfile: %s\n", strerror(errno)), 0);
			dup2(mini.outfile, STDOUT_FILENO);		
		}
		else if (current_token->type == T_LESS && current_token->next)
		{
			mini.infile = open(current_token->next->value, O_RDONLY);
			if (mini.infile < 0)
				return (printf("Error infile: %s\n", strerror(errno)), 0);
			dup2(mini.infile, STDIN_FILENO);
		}
		current_token = current_token->next;
	}
	return (1);
}

void	exec(t_mini mini, char **env)
{
	pid_t	pid;

	 	if (has_redirection(mini) == 0)
		return ;
 	if (ft_is_builtin(mini.token->value))
	{
		ft_exec_builtin(mini.token, mini.enviroment);
		return ;
	}
	mini.path = find_path(env);
	mini.location_paths = ft_split(mini.path, ':');
	pid = fork();
	if (pid == -1)
	{
		free(mini.path);
		free(mini.location_paths);
		printf("Fork failed to create a new process.");
		return ;
	}
	else if (pid == 0)
	{
		first_child(mini, env);
		exit (1);
	}
	wait (NULL);
	if (mini.location_paths)
		free(mini.location_paths);
	return ;
}
