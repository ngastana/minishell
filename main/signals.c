/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/25 19:10:56 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	signals_sigin(int mini)
{
	(void) mini;
/*	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); */
	exit (1);
}

void	signals_sigout(int mini)
{
	(void) mini;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	ft_signals(void)
{
	signal(SIGINT, signals_sigin); //solo deberia de funcionar el control c
	signal(SIGQUIT, SIG_IGN);
}
