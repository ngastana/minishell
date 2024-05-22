/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:26:43 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 19:33:10 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int has_redirection(t_mini *mini)
{
	t_token	*current_token;

	current_token = mini->token;
	mini->outfile = STDOUT_FILENO;
	mini->infile = STDIN_FILENO;
	while (current_token && current_token->type != T_PIPE)
	{
		if (current_token->type == T_GREAT && current_token->next)
		{
			mini->outfile = open(current_token->next->value, O_TRUNC | O_CREAT | O_RDWR, 0777);
			if (mini->outfile < 0)
				return (printf("Error outfile: %s\n", strerror(errno)), 0);
		}
		else if (current_token->type == T_DGREAT && current_token->next)
		{
			mini->outfile = open(current_token->next->value, O_CREAT | O_APPEND | O_RDWR, 0777);
			if (mini->outfile < 0)
				return (printf("Error outfile: %s\n", strerror(errno)), 0);	
		}
		else if (current_token->type == T_LESS && current_token->next)
		{
			mini->infile = open(current_token->next->value, O_RDONLY);
			if (mini->infile < 0)
				return (printf("Error infile: %s\n", strerror(errno)), 0);
		}
		current_token = current_token->next;
	}
	return (1);
}
