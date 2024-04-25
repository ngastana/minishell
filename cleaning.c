/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:03:12 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/25 18:40:59 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

static void	ft_clear(char **matrix)
{
	int	m;

	m = 0;
	while (matrix[m] != NULL)
	{
		free (matrix[m]);
		m++;
	}
	free (matrix);
}

void	ft_clean(t_mini mini)
{
	ft_clear(mini.enviroment);
/* 	ft_lstclear(&mini.token,ft_del);
	ft_lstclear(&mini.parsed,ft_del); */
	if (mini.path)
		free(mini.path);
	if (mini.location_paths)
		ft_clear(mini.location_paths);
}
