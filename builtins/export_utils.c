/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:06:56 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 22:25:38 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int search_export(char *str, char **export)
{
	int i;
	int len;
	
	i = 0;
	while (export[i])
	{
		len = 0;
		while (export[i][len] != '=' && export[i][len] != '\0')
			len++;
		if (!ft_strncmp(str,export[i],len))
			return (1);
		i++;
	}
	return (0);
}

int	check_value(char *str)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	return(printf(" export: `%c': not a valid identifier", str[0]) , 0);
}

char **add_to_export(char *str, char **export)
{
	int	count;
	char **tmp_export;

	count = 0;
	while (export[count])
		count++;
	tmp_export = ft_calloc(sizeof(char *), (count + 2));
	count = -1;
	while (export[++count])
		tmp_export[count] = ft_strdup(export[count]);	
	tmp_export[count] = ft_strdup(str);
	ft_clear(export);
	export_sort(tmp_export);
	return (tmp_export);
}

void	change_value(char *str, char **export)
{
	int i;
	int len;

	i = 0;
	while (export[i])
	{
		len = 0;
		while (export[i][len] != '=' && export[i][len] != '\0')
			len++;
		if (!ft_strncmp(str,export[i],len))
		{
			free(export[i]);
			export[i] = ft_strdup(str);
			export_sort(export);
			return ;
		}
		i++;
	}
}

void add_to_env(char *str, char **env, int flag)
{
	int i;
	int len;

	i = 0;
	if (flag == 0) //noesta
	{	
		while (env[i])
			i++;
		env[i] = ft_strdup(str);
		env[++i] = NULL;
		i = -1;
	}
	else if (flag == 1) //siesta
	{
		while (env[i])
		{
			len = 0;
			while (env[i][len] != '\0' && env[i][len] != '=')
				len++;
			if (!ft_strncmp(str,env[i],len))
			{
				free(env[i]);
				env[i] = ft_strdup(str);
				return ;
			}
			i++;
		}
	}
}