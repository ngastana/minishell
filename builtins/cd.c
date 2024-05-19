/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana <ngastana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:32:21 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/19 12:48:25 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env(char *old_env, char *new_env)
{
	char	*new_env_str;
	int		i;

	i = 0;
	while (g_mini.enviroment[i] && (ft_strncmp(old_env, g_mini.enviroment[i], ft_strlen(old_env))))
		i++;
	if (g_mini.enviroment[i])
	{
		new_env_str = malloc(sizeof(char) * (ft_strlen(old_env) + ft_strlen(new_env) + 1));
		if (!new_env_str)
			return ;
		ft_strlcpy(new_env_str, g_mini.enviroment[i], ft_strlen(old_env) +1);
		new_env_str[ft_strlen(old_env)] = '=';
		ft_strlcpy(new_env_str + ft_strlen(old_env) +1, new_env, ft_strlen(new_env) +1);		
		free (g_mini.enviroment[i]);
		g_mini.enviroment[i] = new_env_str;
	}
}

static char *get_envlst(char *new_env)
{
	int i;

	i = 0;
	while (g_mini.enviroment[i])
	{
		if (ft_strncmp(new_env, g_mini.enviroment[i], ft_strlen(new_env)) == 0)
			return (g_mini.enviroment[i] + ft_strlen(new_env) + 1);
		i++;
	}
	return (NULL);
}

static void	go_home(void)
{
	char	*home;

	update_env("OLDPWD", get_envlst("PWD"));
	home = get_envlst("HOME");
	if (!home)
		ft_putstr_fd(": cd: HOME not set\n", 2);
	else if (chdir(home) == 0)
		update_env("PWD", home);
}

int	ft_cd(t_token *current)
{
	char	*cwd;
	char	*oldpwd;
	
	if (!search_in_matrix("OLDPWD", g_mini.enviroment))
		g_mini.enviroment = add_to_matrix("OLDPWD", g_mini.enviroment);
 	if (!search_in_matrix("PWD", g_mini.enviroment))
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			g_mini.enviroment = add_to_matrix(ft_strjoin("PWD=", cwd), g_mini.enviroment);
			free(cwd);
		}
	}
	if (!current || (current->value[0] == '~' && current->value[1] == '\0') ||
	 (current->value[0] == '-' && current->value[1] == '-' && current->value[2] == '\0'))
		return (go_home(), 0);
	else if ((current->value[0] == '-' && current->value[1] == '\0'))
	{
        oldpwd = get_envlst("OLDPWD");
        if (oldpwd)
        {
            update_env("PWD", oldpwd);
            printf("%s\n", oldpwd);
            chdir(oldpwd);
        }
        else
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
        }
        return 0;
	}
	if (chdir(current->value) != 0)
	{
		perror("cd");
		return (printf("a donde vas majo\n"), 1);
	}
	update_env("OLDPWD", get_envlst("PWD"));
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env("PWD", cwd);
		free (cwd);
	}
	else
	{
		perror ("cd");
		return (printf("a donde vas majo\n"), 1);
	}
	return (0);
}
