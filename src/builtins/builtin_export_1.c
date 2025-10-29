/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:54:24 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 18:34:42 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_single_var(char *var)
{
	char	*new_var;
	int		equal_sign;

	equal_sign = 0;
	new_var = ft_strdup(var);
	char_search(new_var, "=", &equal_sign);
	if (equal_sign >= 0)
	{
		new_var = str_add_at(new_var, '\"', equal_sign + 1);
		printf("declare -x %s\"\n", new_var);
	}
	else
		printf("declare -x %s\n", new_var);
	free(new_var);
}

int	print_export(char **envp, t_exit *shell_state)
{
	char	**temp_envp;
	int		i;

	temp_envp = sorted_copy(envp);
	i = 0;
	while (temp_envp[i])
	{
		if (temp_envp[i][0] != '-')
			print_single_var(temp_envp[i]);
		i++;
	}
	ft_free_array(&temp_envp);
	shell_state->exit_code = 0;
	return (0);
}

int	find_var_index(char **envp, char *name, int len)
{
	int	i;
	int	skip;

	i = 0;
	while (envp[i])
	{
		skip = 0;
		if (envp[i][0] == '-')
			skip = 1;
		if (ft_strncmp(envp[i] + skip, name, len) == 0)
			if (envp[i][skip + len] == '=' || envp[i][skip + len] == '\0')
				return (i);
		i++;
	}
	return (-1);
}

char	**expand_env(char ***envp)
{
	char	**new_env;
	int		n;

	n = 0;
	while ((*envp)[n])
		n++;
	new_env = realloc(*envp, (n + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[n + 1] = NULL;
	return (new_env);
}

int	update_declared_var(char ***envp, int idx, char *arg)
{
	if ((*envp)[idx][0] == '-')
	{
		free((*envp)[idx]);
		(*envp)[idx] = ft_strdup(arg);
		if (!(*envp)[idx])
			return (-1);
	}
	return (0);
}
