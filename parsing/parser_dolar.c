/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:04:36 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 18:40:20 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t ft_strlen_same(char *str)
{
	int	i;
	
	i = 0;
	while(str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_find_name(char **env, char *value)
{
	int		i;
	char	*name;
	char	*this;
	int		len;

	i = 0;
	this = NULL;
	while (env[i] != NULL)
	{
		if (ft_strlen_same(env[i]) < ft_strlen(value))
			len = ft_strlen(value);
		else
			len = ft_strlen_same(env[i]);
		if (!ft_strncmp(env[i], value, len))
		{
			name = ft_strdup(env[i]);
			this = ft_substr(name, ft_strlen_same(env[i]) +1, ft_strlen(env[i]));
			free (name);
			return(this);
		}
		i++;
	}
	return(this);
}

int	parser_dolar(t_mini *mini)
{
	t_token *cur_token;
	int		i;
	char	*name;
	char	*true_value;

	cur_token = mini->token;
	while (cur_token)
	{
		if (cur_token->type == T_IDENTIFIER)
		{
			i = 0;
			while(cur_token->value[i])
			{
				if (cur_token->value[i] == '$' && cur_token->quotation_mark != 1 && cur_token->value[i +1] != '\0')
				{
					if (cur_token->quotation_mark != 1)
					{
						i++;
						true_value = ft_substr(cur_token->value, 0 ,i -1);
						name = ft_find_name(mini->enviroment, cur_token->value + i);
						if (cur_token->value)
							free (cur_token->value);
						if (!name)
						{
							free (name);
							cur_token->value = true_value;
							break;
						}
					}
					cur_token->value = ft_strjoin(true_value, name);
					free(true_value);
					free(name);
					break ;
				}
				i++;
			}
		}
		cur_token = cur_token->next;
	}
/* 	while (mini.token)
	{
		printf("MINI: %s\n", mini.token->value);
		mini.token = mini.token->next;
	} */
	return (0);
}
