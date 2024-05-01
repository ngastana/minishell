/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:32:21 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/01 16:56:08 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void update_env(char *old_env, char *new_env, char **env)
{
	size_t i;
	size_t j;
	static int memo;
    char *new_env_str;

	i = -1;
	j = 0;
	while (ft_strncmp(old_env, *env, ft_strlen(old_env)) && env)
		env++;
	if (env)
	{
		new_env_str = malloc(sizeof(char *) * (ft_strlen(old_env) + ft_strlen(new_env) + 1));
		if (!new_env_str)
			return ;
		ft_strlcpy(new_env_str, *env, ft_strlen(old_env) +1);
		new_env_str[ft_strlen(old_env)] = '=';
		ft_strlcpy(new_env_str + ft_strlen(old_env) +1, new_env, ft_strlen(new_env) +1);		
		new_env_str[ft_strlen(old_env) + ft_strlen(new_env) + 1] = '\0';
		*env = new_env_str;
		memo = 1;
	}
}

static char *get_envlst(char *new_env, char **env)
{
	while (ft_strncmp(new_env, *env, ft_strlen(new_env)))
		env++;
	return (*env + ft_strlen(new_env) +1);
}

static void	go_home(char **env)
{
	char	*home;

	update_env("OLDPWD", get_envlst("PWD", env), env);
	home = get_envlst("HOME", env);
	if (!home)
		ft_putstr_fd(": cd: HOME not set\n", 2);
	else if (chdir(home) == 0)
		update_env("PWD", home, env);		
}

int	ft_cd(t_token *current, char **env)
{
	char	*cwd;
	
 	if (!current || (current->value[0] == '~' && current->value[1] == '\0') ||
	 (current->value[0] == '-' && current->value[1] == '-' && current->value[2] == '\0'))
		return (go_home(env), 0);
	else if ((current->value[0] == '-' && current->value[1] == '\0'))
	{
		update_env("PWD", get_envlst("OLDPWD", env), env);
		return (printf("%s\n", get_envlst("PWD", env)), 0);
	}
	if (chdir(current->value) != 0)
		return (printf("a donde vas majo\n"), 1);
	update_env("OLDPWD", get_envlst("PWD", env), env);
	cwd = getcwd(NULL, 0);
	if (cwd)
		update_env("PWD", cwd, env);
	else
		return (printf("a donde vas majo\n"), 1);
	return (0);
}
