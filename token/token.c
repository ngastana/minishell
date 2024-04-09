/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:25:21 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/09 15:04:50 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token(char *input)
{
	int		found;
	t_token	*token;

	found = 1;
	token = NULL;
	while (*input)
	{
		if (!found)
			return (NULL);
		if (ft_space(*input))
			input = ft_skip_spaces(input);
		else if (!ft_strncmp(input, "<", 1) || !ft_strncmp(input, ">", 1)
			|| !ft_strncmp(input, "|", 1) || !ft_strncmp(input, "&&", 2)
			|| !ft_strncmp(input, "(", 1) || !ft_strncmp(input, ")", 1))
			found = ft_handle_token(&input, &token);
		else
			found = ft_without_token(&input, &token);
/* 		while (token != NULL)
		{
			printf("-Valores de los tokens: %s\n", token->value);
			printf("--Tipo del valor de los tokens: %u\n", token->type);
			token = token->next;
		} */
	}
	return (token);
}