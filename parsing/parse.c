/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:30:33 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 13:06:31 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_mini mini)
{
	parse_consecutive_token(mini);
	parse_DLESS_token(mini);;
	parser_dolar(mini);
	parse_PIPE_token(mini);
}
