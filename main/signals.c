/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emunoz <emunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/29 17:27:03 by emunoz           ###   ########.fr       */
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