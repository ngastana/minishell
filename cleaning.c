/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:03:12 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 19:21:48 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_clear_token(t_token *token)
{
	while (token)
	{
		if (token->value)
			free(token->value);
		token = token->next;
	}
} */

void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_clear(char **matrix)
{
	int	m;

	m = 0;
	if (!matrix)
		return ;
	while (matrix[m] != NULL)
	{
		free (matrix[m]);
		m++;
	}
	matrix = NULL;
}

void	ft_clean(t_mini *mini)
{
	ft_clear(mini->enviroment);
	ft_clear(mini->export);
	ft_clear_token(&mini->token);
	free(mini);
 	// ft_lstclear((t_list**)mini->token,ft_del);
	// ft_lstclear((t_list**)mini->parsed,ft_del);
}
