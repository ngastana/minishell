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

int	ft_is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (1);
	return (0);
}

int ft_without_token(char **line, t_token **token)
{
	char	*tmp_line;
	size_t	i;

	(void) token;
	tmp_line = *line;
	i = 0;
	while (line[i] && !ft_is_separator(tmp_line + i))
	{
		printf("%s", line[i]);
		i++;
	}
	return (1);
}
