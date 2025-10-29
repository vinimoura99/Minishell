/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:55:41 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 18:29:18 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	declare_export(char *arg, char ***envp, char **new_env, char *new_var)
{
	int	idx;
	int	n;

	idx = find_var_index(*envp, arg, ft_strlen(arg));
	if (idx != -1)
	{
		if (update_declared_var(envp, idx, arg) == -1)
			return (-1);
		free(new_var);
		return (0);
	}
	new_env = expand_env(envp);
	if (!new_env)
		return (-1);
	n = 0;
	while (new_env[n])
		n++;
	new_env[n] = new_var;
	*envp = new_env;
	return (0);
}

char	*extract_var_name(char *arg)
{
	int		len;
	char	*name;

	len = 0;
	while (arg[len] && arg[len] != '=' && arg[len] != '+')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, arg, len + 1);
	return (name);
}

char	*get_old_value(char *env_str)
{
	char	*eq_pos;

	eq_pos = ft_strchr(env_str, '=');
	if (eq_pos && eq_pos[0] == '=')
		return (eq_pos + 1);
	return ("");
}

char	*concat_str(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + len2 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}

char	*build_full_var(char *name, char *value)
{
	char	*temp;
	char	*result;

	temp = concat_str(name, "=");
	if (!temp)
		return (NULL);
	result = concat_str(temp, value);
	free(temp);
	return (result);
}
