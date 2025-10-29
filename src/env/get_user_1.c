/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:21:37 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/28 09:40:29 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user_env(char **env)
{
	char	*user_env;

	user_env = search_var("USER=", env);
	if (!user_env)
		return (NULL);
	return (user_env);
}

char	*create_pwd_prompt(char *pwd_env)
{
	char	*new_pwd;
	size_t	len;

	if (!pwd_env)
		return (NULL);
	len = ft_strlen(pwd_env) + 3;
	new_pwd = malloc(sizeof(char) * len);
	if (!new_pwd)
		return (NULL);
	ft_strlcpy(new_pwd, pwd_env, len);
	ft_strlcat(new_pwd, "$ ", len);
	free(pwd_env);
	return (new_pwd);
}

char	*assemble_user_prompt(char *user_env, char *temp_pwd, int color)
{
	char	*user;
	int		total_len;

	if (!user_env || !temp_pwd)
		return (NULL);
	total_len = ft_strlen(user_env) + 12 + ft_strlen(temp_pwd) + 16 + 1;
	user = malloc(sizeof(char) * total_len);
	if (!user)
		return (NULL);
	ft_strlcpy(user, user_env, total_len);
	ft_strlcat(user, "@minishell:", total_len);
	if (color == 1)
		ft_strlcat(user, "\001\033[1;35m\002", total_len);
	ft_strlcat(user, temp_pwd, total_len);
	if (color == 1)
		ft_strlcat(user, "\001\033[0m\002", total_len);
	free(user_env);
	free(temp_pwd);
	return (user);
}

char	*get_user(char **env, int color)
{
	char	*user_env;
	char	*pwd_env;
	char	*home_env;
	int		pwd_allocated;

	pwd_allocated = 0;
	user_env = get_user_env(env);
	if (!user_env)
		user_env = ft_strdup("user");
	home_env = search_var("HOME=", env);
	pwd_env = get_pwd_env(env, home_env, &pwd_allocated);
	free(home_env);
	if (!pwd_env || !user_env)
	{
		free_env_vars(user_env, pwd_env, pwd_allocated);
		return (NULL);
	}
	pwd_env = create_pwd_prompt(pwd_env);
	if (!pwd_env)
	{
		free_env_vars(user_env, NULL, 0);
		return (NULL);
	}
	return (assemble_user_prompt(user_env, pwd_env, color));
}
