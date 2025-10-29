/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:29:33 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 16:15:15 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_basic_pwd(char **pwd_env, char **env, int *allocated)
{
	char	*cwd;

	*pwd_env = search_var("PWD=", env);
	*allocated = 1;
	if (!(*pwd_env))
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			*pwd_env = ft_strdup(".");
		else
			*pwd_env = cwd;
		if (!(*pwd_env))
			*allocated = 0;
	}
}

static char	*handle_home(char *pwd_env, char *home_env, int *allocated)
{
	char	*new_pwd;

	if (ft_strncmp(pwd_env, home_env, ft_strlen(home_env)) == 0)
	{
		new_pwd = ft_strjoin("~", pwd_env + ft_strlen(home_env));
		if (*allocated)
			free(pwd_env);
		*allocated = 1;
		return (new_pwd);
	}
	return (pwd_env);
}

char	*get_pwd_env(char **env, char *home_env_param, int *allocated)
{
	char	*pwd_env;
	char	*home_env;

	get_basic_pwd(&pwd_env, env, allocated);
	if (home_env_param)
		home_env = ft_strdup(home_env_param);
	else
		home_env = search_var("HOME=", env);
	if (home_env)
	{
		pwd_env = handle_home(pwd_env, home_env, allocated);
		free(home_env);
	}
	return (pwd_env);
}
