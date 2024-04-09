/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:04:36 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/09 17:00:54 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t ft_strlen_upper(char *str)
{
	int	i;
	
	i = 0;
	while(str[i] >= 'A' && str[i] <= 'Z')
		i++;
	return (i);
}

char	*ft_find_name(char **env, char *value)
{
	int		i;
	char	*name;
	char	*this;
	int		len;

	i = 0;
	while (env[i] != NULL && i >= 0)
	{
		if (ft_strlen_upper(env[i]) < ft_strlen(value))
			len = ft_strlen(value);
		else
			len = ft_strlen_upper(env[i]);
		if (!ft_strncmp(env[i], value, len))
		{
			name = ft_strdup(env[i]);
			this = ft_substr(name, ft_strlen_upper(env[i]) +1, ft_strlen(env[i]));
			free (name);
			i = -2;
		}
		i++;
	}
	return(this);
}

void	parser_dolar(t_mini mini)
{
	t_token *cur_token;
	int		i;
	char	*name;
	char	*true_value;

	cur_token = mini.token;
	i = 0;
	printf("%s\n",cur_token->value);
	while (cur_token->value)
	{
		if (cur_token->type == T_IDENTIFIER)
		{
			while(cur_token->value[i])
			{
				if (cur_token->value[i] == '$')
				{
					i++;
					true_value = ft_substr(cur_token->value, 0 ,i -1);
					name = ft_find_name(mini.enviroment, cur_token->value + i);	
					cur_token->value = NULL;
					cur_token->value = ft_strjoin(true_value, name);
					printf("IDENTIFICAR: %s\n", cur_token->value);
					break ;
				}
				i++;
			}
			i = 0;
		}
		cur_token = cur_token->next;
	}
	mini.token = cur_token;
}
