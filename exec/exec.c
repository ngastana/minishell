/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:59:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 21:56:10 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && ft_strncmp("PATH", envp[i], 4))
		i++;
	return (ft_strdup(envp[i] + 5));
}

char *get_comands(t_token *cur_token)
{
	char *str1;
	t_token	*token;

	token = cur_token;
	str1 = ft_strdup(token->value);
	while (token->next && (token->next->type == T_IDENTIFIER || token->next->type == T_LESS))
	{
		token = token->next;
		if (token->next && token->type == T_LESS)
			token = token->next;
		str1 = ft_strjoin(str1, " ");
		str1 = ft_strjoin(str1, token->value);
	}
	if (token->next)
		token = token->next;
	return (str1);
}

void	ft_child(t_mini *cur_mini)
{
	int		i;
	char	*location;
	char	*tmp;
	char	*aux;

	i = 0;
	aux = get_comands(cur_mini->token);
	cur_mini->comands = ft_split(aux, ' ');
	cur_mini->path = find_path(cur_mini->enviroment);
	cur_mini->location_paths = ft_split(cur_mini->path, ':');
	free (aux);
	while (cur_mini->location_paths[i] != NULL) 
	{
		tmp = ft_strjoin(cur_mini->location_paths[i], "/");
		location = ft_strjoin(tmp, cur_mini->comands[0]);
		if (access(location, X_OK) == 0)
		{
			if (execve(location, cur_mini->comands, cur_mini->enviroment) == -1)
				printf("Error execve\n");
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);	
			free(location);
			free(tmp);
			ft_clear(cur_mini->comands);
			exit(EXIT_FAILURE);
		}
		i++;
		free(location);
		free(tmp);
	}
	if (cur_mini->location_paths)
		ft_clear(cur_mini->location_paths);
	if (cur_mini->path)
		free(cur_mini->path);
	ft_clear(cur_mini->comands);
	exit(EXIT_FAILURE);
}

void	create_child(t_mini *cur_mini)
{
	int		original_stdout;
	int		original_stdin;
	pid_t	pid;
	int		count_pipex;

	count_pipex = 0;
	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	while (count_pipex <= cur_mini->nbr_pipex)
	{
		if (!has_redirection(cur_mini))
			return ;
		if (count_pipex < cur_mini->nbr_pipex)
		{
			if (pipe(cur_mini->fd) < 0)
			{
				printf("Error doing pipe\n");
				return ;
			}
		}
		if (cur_mini->outfile > 1)
		{
			dup2(cur_mini->outfile, STDOUT_FILENO);
			close(cur_mini->outfile);
		}
		else if(cur_mini->nbr_pipex != count_pipex)
		{
			dup2(cur_mini->fd[1], STDOUT_FILENO);
			close(cur_mini->fd[1]);
		}
		if (cur_mini->infile > 1)
		{
			dup2(cur_mini->infile, STDIN_FILENO);
			close(cur_mini->infile);
		}
		else if (count_pipex != 0)
		{
			dup2(cur_mini->fd[0], STDIN_FILENO);
			close(cur_mini->fd[0]);
		}
		if (ft_is_builtin(cur_mini->token->value))
			ft_exec_builtin(cur_mini, cur_mini->token);
		else
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				ft_child(cur_mini);
				exit(EXIT_SUCCESS);
			}
			else
				waitpid(pid, &g_status, 0);
		}
		while (cur_mini->token && cur_mini->token->type != T_PIPE)
			cur_mini->token = cur_mini->token->next;
		if (cur_mini->token && cur_mini->token->type == T_PIPE)
			cur_mini->token = cur_mini->token->next;
		count_pipex++;
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
	}
	close(original_stdout);
	close(original_stdin);
	return ;
}

static int	count_pipex(t_mini *mini)
{
	t_token	*tmp_token;
	int		i;

	tmp_token = mini->token;
	i = 0;
	while (tmp_token)
	{
		if (tmp_token->type == T_PIPE)
			i++;
		tmp_token = tmp_token->next;
	}
	return (i);
}

void	exec(t_mini *mini)
{
	t_mini	*cur_mini;

	cur_mini = mini;
	cur_mini->nbr_pipex = count_pipex(cur_mini);
	create_child(cur_mini);
	return ;
}
