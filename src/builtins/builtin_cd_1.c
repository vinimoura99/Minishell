/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:47:14 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 01:14:46 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_key_val(const char *key_eq, const char *val)
{
	size_t	len;
	char	*s;

	len = ft_strlen(key_eq) + ft_strlen(val) + 1;
	s = malloc(len);
	if (!s)
		return (NULL);
	ft_strlcpy(s, key_eq, len);
	ft_strlcat(s, val, len);
	return (s);
}

int	append_kv_to_env(char ***env, char *kv)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(kv);
		return (-1);
	}
	i = 0;
	while (i < count)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[count] = kv;
	new_env[count + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	update_env_var(char ***env, const char *key_eq, const char *val)
{
	int		i;
	char	*kv;

	kv = join_key_val(key_eq, val);
	i = get_str_index(*env, (char *)key_eq, 1);
	if (!kv)
		return (-1);
	if (i != -1)
	{
		free((*env)[i]);
		(*env)[i] = kv;
		return (0);
	}
	return (append_kv_to_env(env, kv));
}

int	do_cd_dash(char ***env, char **oldpwd_val)
{
	*oldpwd_val = search_var("OLDPWD=", *env);
	if (!(*oldpwd_val))
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
		return (2);
	}
	if (chdir(*oldpwd_val) == -1)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

int	do_cd_home(char ***env)
{
	char	*home;

	home = search_var("HOME=", *env);
	if (!home)
	{
		write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		return (2);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		free(home);
		return (-1);
	}
	free(home);
	return (0);
}
