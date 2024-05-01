/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:45:18 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 18:14:20 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void swap_strings(char **a, char **b) 
{
	char *temp = *a;
	*a = *b;
	*b = temp;
}

static int	ft_char_type(int c)
{
	if (c >= 97 && c <= 122) // min
		return (0);
	else if (c >= 65 && c <= 90) // mayus
		return (1);
	else if ( c == '_')
		return (2);
	return (-1);
}

static int compare_strings(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i] != '\0' && str2[j] != '\0') 
	{
		if (ft_char_type(str1[i]) != ft_char_type(str2[j])) 
			return (ft_char_type(str1[i]) - ft_char_type(str2[j]));
        if (str1[i] != str2[j])
            return (str1[i] - str2[j]);
		i++;
		j++;
    }
	return (ft_strlen(str1) - ft_strlen(str2));
}

void export_sort(char **export) 
{
	int count;
	int i;
	int j;

	count = 0;
	i = -1;
	while (export[count])
		count++;
    while (++i < count - 1) 
	{
		j = -1;
        while (++j < count - i - 1)
            if (compare_strings(export[j], export[j + 1]) > 0) 
                swap_strings(&export[j], &export[j + 1]);
    }
}