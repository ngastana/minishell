/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_consecutive_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:51:03 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 16:01:45 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parse_consecutive_token(t_mini mini)
{
	t_token	*cur_token;

	cur_token = mini.token;
	while (cur_token)
	{
		if (cur_token->type != T_IDENTIFIER)
			if (cur_token->next != NULL && cur_token->next->type != T_IDENTIFIER)
			{
				printf("syntax error near unexpected token `newline'\n");
				return ;
			}
		cur_token = cur_token->next;
	}
	cur_token = mini.token;	
	while (cur_token)
	{
		if (cur_token->type != T_IDENTIFIER && cur_token->type != T_C_PARENT)
			if(!cur_token->next)
			{
				printf("syntax error near unexpected token `newline'\n");
				return ;
			}
		cur_token = cur_token->next;
	}
}
