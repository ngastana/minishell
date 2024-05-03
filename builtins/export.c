/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:09:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/03 18:20:38 by ngastana         ###   ########.fr       */
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

int ft_export(t_token *token, char **env)
{
	static char	**export;
	static int flag;
	t_token	*current;
 
	current = token;
	if (flag == 0)
	{
		export = create_matrix(env, 0);
		export_sort(export);
		flag = 1;
	}
	if (!token)
		return (print_export(export), 0);
	else
		while (current)
		{
			if (!check_value(current->value))
			{
				current = current->next;
				continue ;
			}
			else if (!search_in_matrix(current->value, export)) //nosta
			{
				export = add_to_matrix(current->value, export);
				if (ft_strchr(current->value, '='))
					env = add_to_matrix(current->value, env);
			}
			else //siesta
			{
				change_value(current->value, export);
				if (search_in_matrix(current->value, env))
					change_value(current->value, env);
				else if (ft_strchr(current->value, '='))
					env = add_to_matrix(current->value, env);
			}
			ft_env(env);			
			if (!current->next)
				return (0);
			current = current->next;
		}
		
	return (0);
}
