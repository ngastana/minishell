/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:25:08 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 18:32:55 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_builtin(t_mini *mini, t_token *token)
{
	t_token *current;
	
	current = token;
	if (ft_compare(current->value, "echo") == 0)
		return (ft_echo(token));
	if (ft_strncmp(current->value, "cd", 2) == 0)
		return (ft_cd(mini, current->next));
	if (ft_compare(current->value, "env") == 0)
		return (ft_env(mini->enviroment));
	if (ft_compare(current->value, "pwd") == 0)
		return (ft_pwd());
	if (ft_strncmp(current->value, "export", 6) == 0)
		return (ft_export(mini, current->next));
	if (ft_strncmp(current->value, "unset", 5) == 0)
		return (ft_unset(mini, current->next));
	return (1);
}

int	ft_is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_compare(arg, "echo")
		|| !ft_compare(arg, "cd")
		|| !ft_compare(arg, "exit")
		|| !ft_compare(arg, "pwd")
		|| !ft_compare(arg, "export")
		|| !ft_compare(arg, "unset")
		|| !ft_compare(arg, "env"))
		return (1);
	return (0);
}
