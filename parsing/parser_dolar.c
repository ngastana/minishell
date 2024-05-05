/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:04:36 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 16:10:08 by ngastana         ###   ########.fr       */
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

static char	*ft_find_name(char *value)
{
	int		i;
	char	*name;
	char	*this;
	int		len;

	i = 0;
	this = NULL;
	while (g_mini.enviroment[i] != NULL)
	{
		if (ft_strlen_same(g_mini.enviroment[i]) < ft_strlen(value))
			len = ft_strlen(value);
		else
			len = ft_strlen_same(g_mini.enviroment[i]);
		if (!ft_strncmp(g_mini.enviroment[i], value, len))
		{
			name = ft_strdup(g_mini.enviroment[i]);
			this = ft_substr(name, ft_strlen_same(g_mini.enviroment[i]) +1, ft_strlen(g_mini.enviroment[i]));
			free (name);
			return(this);
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
						name = ft_find_name(cur_token->value + i);
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
}
