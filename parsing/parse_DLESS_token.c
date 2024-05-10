/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_DLESS_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:41:15 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 15:36:06 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void DLESS_function(t_token	*cur_token)
{
	g_mini.flying = true;
	while (ft_compare(readline(BOLD YELLOW "> " RESET), cur_token->value) && g_mini.flying == true)
			write (1, "", 1);
	g_mini.flying = false;	
	return;
}

int parse_DLESS_token(void)
{
	t_token	*cur_token;

	cur_token = g_mini.token;
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
