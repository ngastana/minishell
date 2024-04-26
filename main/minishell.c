/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:21:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/26 16:15:56 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_mini	initialize_minishell(char **env)
{
	t_mini	mini;

	ft_memset(&mini, 0, sizeof(t_mini));
	mini.enviroment = env;
	return (mini);
}

void	take(char *input)
{
	if (!input || !ft_strncmp(input, "exit", 4))
	{
		ft_putstr_fd("exit\n", 1);
		exit (1);
	}
	if (input)
		add_history(input);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*input;
	t_mini	copy;

	((void)argc, (void)argv);
	mini = initialize_minishell(env);
	while (1)
	{
		input = readline(BOLD YELLOW "Minishel-3.2$ " RESET);
		ft_signals();
		if (input)
		{
			take(input);
			mini.token = ft_token(input);
			if (!mini.token)
				continue ;
			parser_dolar(mini);
			parse_token(mini);
 			copy = mini;
			while (copy.token != NULL)
			{
				printf("Valores de los tokens: %s\n", copy.token->value);
				printf("Tipo del valor de los tokens: %u\n", copy.token->type);
				copy.token = copy.token->next;
			}
			exec(mini, env);
//			ft_clean(mini);			
			free(input);
		}
	}
	return (0);
}
