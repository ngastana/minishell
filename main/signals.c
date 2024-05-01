/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 15:52:02 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig) 
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	handle_sigquit(int sig) 
{
    printf("Ctrl-\\ pressed. Quitting.\n");
	(void)sig;
    exit(EXIT_SUCCESS);
}

void	handle_eof(void) 
{
    printf("Ctrl-D pressed. Exiting.\n");
    exit(EXIT_SUCCESS);
}

void	signal_handlers(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}