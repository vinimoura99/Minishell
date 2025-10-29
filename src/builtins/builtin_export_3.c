/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:56:34 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 18:29:15 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_concat_existing(char ***envp, int idx, char *name, char *new_val)
{
	char	*old_val;
	char	*concat_val;
	char	*full_var;

	if ((*envp)[idx][0] == '-')
	{
		full_var = build_full_var(name, new_val);
		if (!full_var)
			return (-1);
		free((*envp)[idx]);
		(*envp)[idx] = full_var;
		return (0);
	}
	old_val = get_old_value((*envp)[idx]);
	concat_val = concat_str(old_val, new_val);
	if (!concat_val)
		return (-1);
	full_var = build_full_var(name, concat_val);
	free(concat_val);
	if (!full_var)
		return (-1);
	free((*envp)[idx]);
	(*envp)[idx] = full_var;
	return (0);
}

int	handle_concat_new(char ***envp, char *name, char *new_val)
{
	char	**new_env;
	char	*full_var;
	int		n;

	full_var = build_full_var(name, new_val);
	if (!full_var)
		return (-1);
	new_env = expand_env(envp);
	if (!new_env)
	{
		free(full_var);
		return (-1);
	}
	n = 0;
	while (new_env[n])
		n++;
	new_env[n] = full_var;
	*envp = new_env;
	return (0);
}

int	process_concat(char *arg, char ***envp)
{
	char	*var_name;
	char	*new_val;
	int		idx;
	int		result;

	var_name = extract_var_name(arg);
	if (!var_name)
		return (-1);
	new_val = ft_strchr(arg, '=') + 1;
	idx = find_var_index(*envp, var_name, ft_strlen(var_name));
	if (idx == -1)
		result = handle_concat_new(envp, var_name, new_val);
	else
		result = handle_concat_existing(envp, idx, var_name, new_val);
	free(var_name);
	return (result);
}

int	update_existing(char ***envp, int idx, char *new_var)
{
	free((*envp)[idx]);
	(*envp)[idx] = new_var;
	return (0);
}

int	add_new_var(char ***envp, char *new_var)
{
	char	**new_env;
	int		n;

	new_env = expand_env(envp);
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	n = 0;
	while (new_env[n])
		n++;
	new_env[n] = new_var;
	*envp = new_env;
	return (0);
}
