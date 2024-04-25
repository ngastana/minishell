/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:05:49 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/25 18:59:22 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo (t_token *token)
{
	t_token	*cur_token;

	cur_token = token;
	cur_token = cur_token->next;
	while (cur_token)
	{
		if (cur_token->next)
			printf("%s ", cur_token->value);
		else
			printf("%s\n", cur_token->value);			
		cur_token = cur_token->next;
    }
	return (0);
}
