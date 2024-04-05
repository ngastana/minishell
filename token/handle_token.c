/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:48:04 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/05 14:17:36 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_token(t_token **token, t_token *new_token)
{
	t_token	*current;

	if (!*token)
	{
		*token = new_token;
		return;
	}
	current = *token;
	while (current && current->next)
		current = current->next;
	current->next = new_token;
	*token = current;
}

static int	ft_have_token(t_token_type type, char **line, t_token **token)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	new_token->value = NULL;
	new_token->type = type;
	ft_add_token(token, new_token);
	(*line)++;
	if (type == T_DLESS || type == T_DGREAT || type == T_OR || type == T_AND)
		(*line)++;
	return (1);
}

int	ft_handle_token(char **line, t_token **token)
{
    (void) token;
	if (!ft_strncmp(*line, "<<", 2))
		return (printf("T_DLESS\n"), ft_have_token(T_DLESS, line, token));
	else if (!ft_strncmp(*line, ">>", 2))
		return (printf("T_DGREAT\n"), ft_have_token(T_DGREAT, line, token));
	else if (!ft_strncmp(*line, "<", 1))
		return (printf("T_LESS\n"), ft_have_token(T_LESS, line, token));
	else if (!ft_strncmp(*line, ">", 1))
		return (printf("T_GREAT\n"), ft_have_token(T_GREAT, line, token));
	else if (!ft_strncmp(*line, "(", 1))
		return (printf("T_O_PARENT\n"), ft_have_token(T_O_PARENT, line, token));
	else if (!ft_strncmp(*line, ")", 1))
		return (printf("T_C_PARENT\n"), ft_have_token(T_C_PARENT, line, token));
	else if (!ft_strncmp(*line, "&&", 2))
		return (printf("T_AND\n"), ft_have_token(T_AND, line, token));
	else if (!ft_strncmp(*line, "||", 2))
		return (printf("T_NL\n"), ft_have_token(T_NL, line, token));
	else
		return (printf("T_PIPE\n"), ft_have_token(T_PIPE, line, token));
}