/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:30:33 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/21 18:37:59 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(t_mini *mini)
{
	if (parse_consecutive_token(mini) == 1)
		return (1);
	if (parse_DLESS_token(mini) == 1)
		return (1);
	if (parser_dolar(mini) == 1)
		return (1);
	if (parse_PIPE_token(mini) == 1)
		return (1);
	return (0);
}
