/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:01:20 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 17:11:10 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_env_var(char *env_var)
{
	if (!ft_strncmp(env_var, "SHLVL", 5) || !ft_strncmp(env_var, "-SHLVL", 6))
		return (update_shlvl(env_var));
	else
		return (ft_strdup(env_var));
}

static char	**add_shlvl_if_missing(char **new_env, int *size)
{
	char	**tmp;
	int		j;

	j = get_str_index(new_env, "SHLVL", 1);
	if (j < 0)
	{
		tmp = realloc(new_env, sizeof(char *) * ((*size) + 2));
		if (!tmp)
			return (ft_free_array(&new_env));
		new_env = tmp;
		new_env[*size] = ft_strdup("SHLVL=1");
		if (!new_env[*size])
			return (ft_free_array(&new_env));
		(*size)++;
	}
	return (new_env);
}

char	**copy_env(char **env, int *og_size, int *color)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = copy_env_var(env[j]);
		if (!new_env[j])
			return (ft_free_array(&env));
		j++;
	}
	new_env = add_shlvl_if_missing(new_env, &i);
	if (!new_env)
		return (NULL);
	*og_size = i;
	new_env[i] = NULL;
	(*color) = define_color(env);
	return (new_env);
}

static char	*create_pwd_string(void)
{
	char	cwd[1024];
	char	*pwd;
	int		total_size;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		cwd[0] = '\0';
	}
	total_size = ft_strlen(cwd) + 4 + 1;
	pwd = malloc(sizeof(char) * (total_size));
	if (!pwd)
		return (NULL);
	ft_strlcpy(pwd, "PWD=", total_size);
	ft_strlcat(pwd, cwd, total_size);
	return (pwd);
}

char	**build_basic_env(int *og_size, int *color)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
		return (NULL);
	new_env[0] = ft_strdup("OLDPWD");
	if (!new_env[0])
		return (ft_free_array(&new_env));
	new_env[1] = create_pwd_string();
	if (!new_env[1])
		return (ft_free_array(&new_env));
	new_env[2] = ft_strdup("SHLVL=1");
	if (!new_env[2])
		return (ft_free_array(&new_env));
	new_env[3] = NULL;
	(*og_size) = 3;
	(*color) = 0;
	return (new_env);
}
