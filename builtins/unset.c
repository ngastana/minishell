/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:58:57 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 16:23:24 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_from(char *str, char **matrix)
{
	int i;
	int len;

	i = 0;
	while (matrix[i] != NULL)
	{
		if (ft_strlen_same(matrix[i]) < ft_strlen(str))
			len = ft_strlen(str);
		else
			len = ft_strlen_same(matrix[i]);
		if (!ft_strncmp(matrix[i], str, len))
		{
			matrix[i] = NULL;
			free(matrix[i]);
			return ;
		}
		i++;
	}
	
}

int ft_unset(t_token *token)
{
	t_token *current;

	current = token;
	if (!current)
		return (0);
	else
	{
		if (search_in_matrix(current->value, g_mini.export))
		{
			remove_from(current->value, g_mini.export);
			if(search_in_matrix(current->value, g_mini.enviroment))
				remove_from(current->value, g_mini.enviroment);
		}
	}
	return (0);
}