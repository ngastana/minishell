/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:05:49 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 17:18:07 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo (t_token *token)
{
	t_token	*cur_token;

	cur_token = token;
	cur_token = cur_token->next;
	while (cur_token != NULL)
	{
		if (cur_token->type == T_PIPE || cur_token->type == T_AND || cur_token->type == T_NL)
			break ;
		if (cur_token->type != T_IDENTIFIER)
		{
			cur_token = cur_token->next;
			cur_token = cur_token->next;
			continue ;			
		}
		if (cur_token != NULL && cur_token->type == T_IDENTIFIER)
			printf("%s ", cur_token->value);
		if (cur_token != NULL)
			cur_token = cur_token->next;
	}
	printf("\n");
	return (0);
}
