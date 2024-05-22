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
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != '\0' || s2[i] != '\0')
		return (1);
	return (0);
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

void	take(char *input, t_mini *mini)
{
	if (!input || !ft_compare(input, "exit") || !ft_strncmp(input, "exit ", 5))
	{
		ft_putstr_fd("exit\n", 1);
		ft_clean(mini);
		rl_clear_history();
		exit (1);
	}
	if (input)
		add_history(input);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_mini	*mini;

	((void)argc, (void)argv);
	mini = NULL;
	initialize_minishell(&mini, env);
	signal_handlers();
	while (1)
	{
		input = readline(BOLD YELLOW "Minishell-3.2$ " RESET);
		if (input)
		{
			take(input, mini);
			mini->token = ft_token(input);
			if (!mini->token || parse(mini) == 1)
				continue ;
			exec(mini);
			ft_clear_token(&mini->token);
			free(input);
		}
		else
			handle_eof(mini);
	}
	return (0);
}
