/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:25:46 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/23 17:10:10 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free (cwd);
	return (0);
}
