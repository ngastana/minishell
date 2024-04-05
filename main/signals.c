/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/04 17:38:23 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	signals_sigin(int mini)
{
	(void) mini;
	printf("\n");
}

static void	signals_sigout(int mini)
{
	(void) mini;
	printf("exit\n");
	exit (1);
}

void	ft_signals(t_mini mini)
{
	(void) mini;
	signal(STDIN, signals_sigin);
	signal(STDOUT, signals_sigout);
}
