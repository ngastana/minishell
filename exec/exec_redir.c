/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:26:43 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 16:56:32 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int has_redirection(t_mini mini)
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
		}
		else if (current_token->type == T_DGREAT && current_token->next)
		{
			mini.outfile = open(current_token->next->value, O_CREAT | O_RDWR, 0777);
			if (mini.outfile < 0)
				return (printf("Error outfile: %s\n", strerror(errno)), 0);	
		}
		else if (current_token->type == T_LESS && current_token->next)
		{
			mini.infile = open(current_token->next->value, O_RDONLY);
			if (mini.infile < 0)
				return (printf("Error infile: %s\n", strerror(errno)), 0);
		}
		current_token = current_token->next;
	}
	return (1);
}
