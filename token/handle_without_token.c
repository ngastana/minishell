/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_without_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:23:41 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/05 14:36:14 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_skip_quote (char *input, int *i)
{
	char	quote;

	quote = input[*i];
	while (ft_strchr(input + *i +1, quote))
	{
		(*i)++;
		while (input[*i] != quote)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int ft_without_token(char **input, t_token **token)
{
	char	*tmp_input;
	int		i;
	char	*value;
	t_token *new_token;

	(void) token;
	tmp_input = *input;
	i = 0;
	while (tmp_input[i] && !ft_is_separator(tmp_input + i))
	{
		if (ft_is_quote(tmp_input[i]))
		{
			if (!(ft_skip_quote(tmp_input, &i)))
			{
				ft_clear_token(token);
				return (printf("CIERRA LA CITA LERDO\n"), 0);
			}
		}
		else	
			i++;
	}
	value = ft_substr(tmp_input, 0, i);
	if (!value)
		return (0);
	new_token = ft_add_new_token(value, T_IDENTIFIER);
	if (!new_token)
		return (free(value), 0);
	*input += i;
	free (value);
	ft_add_token(token, new_token);
	return (1);
}
