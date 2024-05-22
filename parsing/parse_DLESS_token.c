/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_DLESS_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:41:15 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 18:39:02 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void DLESS_function(t_token	*cur_token)
{
	while (ft_compare(readline(BOLD YELLOW "> " RESET), cur_token->value))
			write (1, "", 1);
	return;
}

int parse_DLESS_token(t_mini *mini)
{
	t_token	*cur_token;

	cur_token = mini->token;
	while (cur_token)
	{
		if (cur_token->type == T_DLESS)
		{
			if (cur_token->next != NULL && cur_token->next->type != T_IDENTIFIER)
			{
				printf("Minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			else
			{
				cur_token = cur_token->next;
				if (cur_token == NULL)
				{
					printf ("Minishell: syntax error near unexpected token `newline'\n");
					return (1);	
				}
				DLESS_function(cur_token);
			}
		}
		cur_token = cur_token->next;	
	}
	return (0);
}
