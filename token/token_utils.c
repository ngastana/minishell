/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:37:59 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/05 13:09:16 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (1);
	return (0);
}

char	*ft_skip_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' && ft_space(line[i]))
		i++;
	return (&line[i]);
}

void	ft_clear_token(t_token **token)
{
	t_token	*current_token;
	t_token *next_token;

	if (!*token)
		return;
	current_token = *token;
	while (current_token != NULL)
	{
		free (current_token->value);
		next_token = current_token->next;
		free (current_token);
		current_token = next_token;
	}
	*token = NULL;
}
