/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:21:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 20:54:08 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status;

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

static void	initialize_minishell(t_mini **mini, char **env)
{
	*mini = (t_mini *)malloc(sizeof(t_mini));
	if (*mini == NULL)
	{
		perror("Failed to allocate memory for t_mini");
		exit(EXIT_FAILURE);
	}
	(*mini)->enviroment = create_matrix(env, 1);
	(*mini)->export = create_matrix(env, 0);
	g_status = 0;
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
	t_mini	*mini;
	//t_mini	copy;

	((void)argc, (void)argv);
	mini = NULL;
	initialize_minishell(&mini, env);
	signal_handlers();
	while (1)
	{
		input = readline(BOLD YELLOW "Minishell-3.2$ " RESET);
		//signal_handlers();
		if (input)
		{
			take(input);
			mini->token = ft_token(input);
			if (!mini->token)
				continue ;
			if (parse(mini) == 1)
				continue ;
/* 			copy = mini;
			while (copy.token != NULL)
			{
				printf("Valores de los tokens: %s\n", copy.token->value);
				printf("Tipo del valor de los tokens: %u\n", copy.token->type);
				copy.token = copy.token->next;
			} */
			exec(mini);
			//ft_clean(mini);	
			free(input);
		}
		else
		{
			printf("HANDLE_EOF\n");
			handle_eof();
		}
	}
	return (0);
}
