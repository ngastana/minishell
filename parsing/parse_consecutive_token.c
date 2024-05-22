/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_consecutive_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:51:03 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 19:16:35 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parse_consecutive_token(t_mini *mini)
{
	t_token	*cur_token;

	cur_token = mini->token;
	while (cur_token)
	{
		if (cur_token->type != T_IDENTIFIER)
			if (cur_token->next != NULL && cur_token->next->type != T_IDENTIFIER  
			&& cur_token->next->type != T_LESS && cur_token->next->type != T_DLESS
			&& cur_token->next->type != T_GREAT)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
		cur_token = cur_token->next;
	}
	cur_token = mini->token;	
	while (cur_token)
	{
		if (cur_token->type != T_IDENTIFIER && cur_token->type != T_C_PARENT)
			if(!cur_token->next)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
		cur_token = cur_token->next;
	}
	return (0);
}
