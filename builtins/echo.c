/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:05:49 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/30 17:33:28 by ngastana         ###   ########.fr       */
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
		if (cur_token->type != T_IDENTIFIER)
		{
			cur_token = cur_token->next;
			cur_token = cur_token->next;			
		}
		if (cur_token != NULL && cur_token->next == NULL && cur_token->type == T_IDENTIFIER)
			printf("%s\n", cur_token->value);			
		else if (cur_token != NULL && cur_token->type == T_IDENTIFIER )
			printf("%s ", cur_token->value);
		if (cur_token != NULL)
			cur_token = cur_token->next;
	}
	return (0);
}
