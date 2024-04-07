/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:21:13 by ngastana          #+#    #+#             */
/*   Updated: 2024/04/05 13:27:54 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_mini initialize_minishell(char **env)
{
	t_mini	mini;

	ft_memset(&mini, 0, sizeof(t_mini));
	mini.enviroment = env;
	return (mini);
}

static void	initialize_input(t_mini *mini, char *input)
{
	char	**split_space;
	int		i;
	t_in	*head;
	t_in	*current;
	t_in	*new_node;

	i = 0;
	split_space = ft_split(input, ' ');
	if (split_space == NULL)
		return ;
	head = NULL;
	current = NULL;
	while (split_space[i] != NULL)
	{
		new_node = (t_in *)malloc(sizeof(t_in));
		if (new_node == NULL)
			return ;
		new_node->content = split_space[i];
		new_node->next = NULL;
		if (head == NULL)
		{
			head = new_node;
			current = new_node;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		i++;
	}
	mini->in = head;
	free(split_space);
}

void	take (char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		exit (1);
	}
	if (*input)
		add_history(input);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*input;

	((void)argc, (void)argv);
	mini = initialize_minishell(env);
	while (1)
	{
		input = readline("🤯Minishell >");		
		ft_signals(mini);
		take(input);
		if (*input)
		{
			initialize_input(&mini, input);
			if (mini.in->content != NULL)
			{
				mini.token = ft_token(input);
//				exec(mini, env);
				while (mini.in != NULL)
				{
					printf("DENTRO DEL SPLIT: %s\n", mini.in->content);
					mini.in = mini.in->next;
				}
			}
			free(input);
		}
	}
	return (0);
}
