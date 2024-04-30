/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/30 16:48:41 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig) 
{
   	printf("\n");
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