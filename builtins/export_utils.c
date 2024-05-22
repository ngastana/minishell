/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:06:56 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/19 13:02:50 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int search_in_matrix(char *str, char **export)
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
	return(printf(" export: `%c': not a valid identifier\n", str[0]) , 0);
}

char **add_to_matrix(char *str, char **export)
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
	tmp_export[count + 1] = NULL;
	ft_clear(export);
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
			return ;
		}
		i++;
	}
}
