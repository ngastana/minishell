/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:21:16 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/28 15:40:58 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_PIPE_token(void)
{
	t_token	*cur_token;

	cur_token = g_mini.token;
	if (cur_token->type == T_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
//		ft_clear_token(&cur_token);
		return (1);
	}
	if (cur_token)
	{
 		while (cur_token->next != NULL)
			cur_token = cur_token->next;
		if (cur_token->type == T_PIPE)
		{
			printf("syntax error near unexpected token `|'\n");
//			ft_clear_token(&cur_token);
			return (1);
		}
	}
	return (0);
}
