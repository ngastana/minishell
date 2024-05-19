/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:09:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/19 13:26:19 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **create_matrix(char **env, int flag)
{
	int		i;
	char	**export;
	
	i = 0;
	while (env[i] != NULL)
		i++;
	export = ft_calloc(sizeof(char *), (i + flag));
	i = -1;
	if (flag == 0)
		while (env[++i +1] != NULL)
			export[i] = ft_strdup(env[i]);
	else
		while (env[++i] != NULL)
			export[i] = ft_strdup(env[i]);
	return (export);
}

static void print_export(char **export)
{
	int i;
	int	j;

	i = -1;
	export_sort(export);
	while (export[++i])
	{
		j = 0;
		printf("declare -x ");
		while (export[i][j])
		{
			printf("%c", export[i][j]);
			if (export[i][j] == '=')
				printf("\"");
			if (export[i][j + 1] == '\0' && ft_strchr(export[i], '='))
				printf("\"");
			j++;
		}
		printf("\n");
	}
}

int ft_export(t_token *token)
{
	t_token	*current;
 
	current = token;
	if (!token)
		return (print_export(g_mini.export), 0);
	else
		while (current)
		{
			if (!check_value(current->value))
			{
				current = current->next;
				continue ;
			}
			else if (!search_in_matrix(current->value, g_mini.export)) //nosta
			{
				g_mini.export = add_to_matrix(current->value, g_mini.export);
				if (ft_strchr(current->value, '='))
					g_mini.enviroment = add_to_matrix(current->value, g_mini.enviroment);
			}
			else //siesta
			{
				change_value(current->value, g_mini.export);
				if (search_in_matrix(current->value, g_mini.enviroment))
					change_value(current->value, g_mini.enviroment);
				else if (ft_strchr(current->value, '='))
					g_mini.enviroment = add_to_matrix(current->value, g_mini.enviroment);
			}
			current = current->next;
		}
	return (0);
}
