/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:21:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/17 17:50:07 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	g_mini;

int	ft_compare(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return ((*s1 || *s2) ? 1 : 0);
}

static t_mini	initialize_minishell(char **env)
{
	t_mini	mini;

	ft_memset(&mini, 0, sizeof(t_mini));
	mini.enviroment = create_matrix(env, 1);
	mini.export = create_matrix(env, 0);
	mini.flying = false;
	mini.outfile = 1;
	mini.infile = 0;
	if (pipe(g_mini.fd) < 0)
	{
		printf("Error doing pipe\n");
	//	ft_clear();
	}
	g_mini.old_outfile = dup(STDOUT_FILENO);
	g_mini.old_infile = dup(STDIN_FILENO);
	return (mini);
}

void	take(char *input)
{
	if (!input || !ft_compare(input, "exit"))
	{
		ft_putstr_fd("exit\n", 1);
		exit (1);
	}
	if (input)
		add_history(input);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	//t_mini	copy;

	((void)argc, (void)argv);
	g_mini = initialize_minishell(env);
	signal_handlers();
	while (1)
	{
		input = readline(BOLD YELLOW "Minishell-3.2$ " RESET);
		//signal_handlers();
		if (input)
		{
			take(input);
			g_mini.token = ft_token(input);
			if (!g_mini.token)
				continue ;
			if (parse() == 1)
				continue ;
/* 			copy = mini;
			while (copy.token != NULL)
			{
				printf("Valores de los tokens: %s\n", copy.token->value);
				printf("Tipo del valor de los tokens: %u\n", copy.token->type);
				copy.token = copy.token->next;
			} */
			exec();
//			ft_clean(mini);	
			free(input);
		}
		else
			handle_eof();
	}
	return (0);
}
