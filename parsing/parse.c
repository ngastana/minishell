/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:30:33 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 15:36:52 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(void)
{
	if (parse_consecutive_token() == 1)
		return (1);
	if (parse_DLESS_token() == 1)
		return (1);
	if (parser_dolar() == 1)
		return (1);
	if (parse_PIPE_token() == 1)
		return (1);
	return (0);
}
