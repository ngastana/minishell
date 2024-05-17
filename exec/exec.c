/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:59:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/17 16:42:35 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char *get_comands(t_mini *cur_mini)
{
	char *str1;

	str1 = ft_strdup(cur_mini->token->value);
	while (cur_mini->token->next && (cur_mini->token->next->type == T_IDENTIFIER || cur_mini->token->next->type == T_LESS))
	{
		cur_mini->token = cur_mini->token->next;
		if (cur_mini->token->next && cur_mini->token->type == T_LESS)
			cur_mini->token = cur_mini->token->next;
		str1 = ft_strjoin(str1, " ");
		str1 = ft_strjoin(str1, cur_mini->token->value);
	}
	if (cur_mini->token->next)
		cur_mini->token = cur_mini->token->next;
	return (str1);
}

void	first_child(t_mini *cur_mini)
{
	int			i;
	char		*location;
	char		*tmp;

	dup2(g_mini.infile, STDIN_FILENO);
	if (cur_mini->nbr_pipex == 0)
		dup2(g_mini.outfile, STDOUT_FILENO);
	else if (g_mini.nbr_pipex != 0)
		dup2(g_mini.fd[1], STDOUT_FILENO);
	g_mini.outfile = g_mini.old_outfile;
	g_mini.infile = g_mini.old_infile;
	i = 0;
	cur_mini->comands = ft_split(get_comands(cur_mini), ' ');
	if (ft_is_builtin(cur_mini->token->value))
		ft_exec_builtin(cur_mini->token);
	while (cur_mini->location_paths[i] != NULL && !ft_is_builtin(cur_mini->token->value))
	{
		tmp = ft_strjoin(cur_mini->location_paths[i], "/");
		location = ft_strjoin(tmp, cur_mini->comands[0]);
		if (access(location, X_OK) == 0)
		{	
			if (execve(location, cur_mini->comands, cur_mini->enviroment) == -1)
				printf("Error execve\n");
			break ;
		}
		i++;
		free (location);
		free (tmp);
	}
	exit (0);
}

void	second_child(t_mini *cur_mini, int count_pipex)
{
	int		i;
	char	*location;
	char	*tmp;

	if (has_redirection(*cur_mini) && g_mini.infile > 1)
		dup2(g_mini.infile, STDIN_FILENO);
	else
		dup2(g_mini.fd[0], STDIN_FILENO);
	if (has_redirection(*cur_mini) && g_mini.outfile != 1)
		dup2(g_mini.outfile, STDOUT_FILENO);
	else if (g_mini.nbr_pipex != count_pipex)
		dup2(g_mini.fd[1], STDOUT_FILENO);
	g_mini.outfile = g_mini.old_outfile;
	g_mini.infile = g_mini.old_infile;
	i = 0;
	cur_mini->comands = ft_split(get_comands(cur_mini), ' ');
	if (ft_is_builtin(cur_mini->token->value))
		ft_exec_builtin(cur_mini->token);
	while (cur_mini->location_paths[i] != NULL && !ft_is_builtin(cur_mini->token->value)) 
	{
		tmp = ft_strjoin(cur_mini->location_paths[i], "/");
		location = ft_strjoin(tmp, cur_mini->comands[0]);
		if (access(location, X_OK) == 0)
		{
			if (execve(location, cur_mini->comands, cur_mini->enviroment) == -1)
				printf("Error execve\n");
		}
		i++;
		free (location);
		free (tmp);
	}
	exit (0);
}


void	create_child(t_mini *cur_mini)
{
	pid_t	pid;
	int		count_pipex;

	count_pipex = 0;
	cur_mini->path = find_path(cur_mini->enviroment);
	cur_mini->location_paths = ft_split(cur_mini->path, ':');
	pid = fork();
	if (pid == -1)
	{
		free(cur_mini->path);
		free(cur_mini->location_paths);
		printf("Fork failed to create a new process.");
		return ;
	}
	else if (pid == 0)
		first_child(cur_mini);
//	wait (NULL);
	while (count_pipex < cur_mini->nbr_pipex)
	{
		while (cur_mini->token->type != T_PIPE)
			cur_mini->token = cur_mini->token->next;
		if (cur_mini->token->type == T_PIPE)
			cur_mini->token = cur_mini->token->next;		
		pid = fork();
		if (pid == -1)
		{
			free(cur_mini->path);
			free(cur_mini->location_paths);
			printf("Fork failed to create a new process.");
			return ;
		}
		count_pipex++;
		if (pid == 0)
			second_child(cur_mini, count_pipex);
	}
	wait (NULL);
}

static int	count_pipex(void)
{
	t_mini	tmp_cur;
	int		i;

	tmp_cur = g_mini;
	i = 0;
	while (tmp_cur.token)
	{
		if (tmp_cur.token->type == T_PIPE)
			i++;
		tmp_cur.token = tmp_cur.token->next;
	}
	return (i);
}

void	exec(void)
{
	static t_mini	cur_mini;

	cur_mini = g_mini;
	cur_mini.nbr_pipex = count_pipex();
	if (has_redirection(cur_mini) == 0)
		return ;
	create_child(&cur_mini);
	wait (NULL);
	g_mini.outfile = g_mini.old_outfile;
	g_mini.infile = g_mini.old_infile;
	if (cur_mini.location_paths)
		free(cur_mini.location_paths);
	return ;
}
