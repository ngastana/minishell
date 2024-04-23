/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:25:08 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/23 19:58:05 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_builtin(t_token *token, char **env)
{
	t_token *current;

	current = token;
	if (ft_strncmp(current->value, "echo", 4) == 0)
		return (ft_echo(token));
/* 	if (ft_strncmp(current->value, "cd", 2) == 0)
		return (ft_cd(current->next->value)); */
	if (ft_strncmp(current->value, "env", 3) == 0)
		return (ft_env(env));
	if (ft_strncmp(current->value, "pwd", 3) == 0)
		return (ft_pwd());
/* 	if (ft_strncmp(current->value, "export", 6) == 0)
		return (ft_export(current->value));
	if (ft_strncmp(current->value, "unset", 5) == 0)
		return (ft_unset(current->value)); */
	return (1);
}

int	ft_is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "echo", 4)
		|| !ft_strncmp(arg, "cd", 2)
		|| !ft_strncmp(arg, "exit", 4)
		|| !ft_strncmp(arg, "pwd", 3)
		|| !ft_strncmp(arg, "export", 6)
		|| !ft_strncmp(arg, "unset", 5)
		|| !ft_strncmp(arg, "env", 3))
		return (1);
	return (0);
}
