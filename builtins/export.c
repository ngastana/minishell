/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:09:42 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 22:07:35 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **create_export(char **env)
{
	int		i;
	char	**export;
	
	i = 0;
	while (env[i] != NULL)
		i++;
	export = ft_calloc(sizeof(char *), (i));
	i = -1;
	while (env[++i +1] != NULL)
		export[i] = ft_strdup(env[i]);
	return (export);
}

int ft_export(t_token *token, char **env)
{
	static char	**export;
	int		i;
	static int flag;
	t_token	*current;

	current = token;
	if (flag == 0)
	{
		export = create_export(env);
		export_sort(export);
		flag = 1;
	}
	if (!token)
	{
		i = -1;
		while (export[++i])
			printf("declare -x %s\n", export[i]);
		return (0);
	}
	else
		while(current)
		{
			if (!check_value(current->value))
				continue ;
			if (!search_export(current->value, export)) //nosta
			{
				export = add_to_export(current->value, export);
				if (ft_strchr(current->value, '='))
					add_to_env(current->value, env, 0);
			}
			else //siesta
			{
				change_value(current->value, export);
				add_to_env(current->value, env, 1);
			}
			if (!current->next)
				return (0);
			current = current->next;
		}
	return (0);
}
