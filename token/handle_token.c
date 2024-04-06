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

t_token	*ft_add_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

static int	ft_have_token(t_token_type type, char **input, t_token **token)
{
	t_token	*new_token;

	new_token = ft_add_new_token(NULL, type);
	if (!new_token)
		return (0);
	ft_add_token(token, new_token);
	(*input)++;
	if (type == T_DLESS || type == T_DGREAT || type == T_OR || type == T_AND)
		(*input)++;
	return (1);
}

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

int	ft_handle_token(char **input, t_token **token)
{
    (void) token;
	if (!ft_strncmp(*input, "<<", 2))
		return (printf("T_DLESS\n"), ft_have_token(T_DLESS, input, token));
	else if (!ft_strncmp(*input, ">>", 2))
		return (printf("T_DGREAT\n"), ft_have_token(T_DGREAT, input, token));
	else if (!ft_strncmp(*input, "<", 1))
		return (printf("T_LESS\n"), ft_have_token(T_LESS, input, token));
	else if (!ft_strncmp(*input, ">", 1))
		return (printf("T_GREAT\n"), ft_have_token(T_GREAT, input, token));
	else if (!ft_strncmp(*input, "(", 1))
		return (printf("T_O_PARENT\n"), ft_have_token(T_O_PARENT, input, token));
	else if (!ft_strncmp(*input, ")", 1))
		return (printf("T_C_PARENT\n"), ft_have_token(T_C_PARENT, input, token));
	else if (!ft_strncmp(*input, "&&", 2))
		return (printf("T_AND\n"), ft_have_token(T_AND, input, token));
	else if (!ft_strncmp(*input, "||", 2))
		return (printf("T_NL\n"), ft_have_token(T_NL, input, token));
	else
		return (printf("T_PIPE\n"), ft_have_token(T_PIPE, input, token));
}