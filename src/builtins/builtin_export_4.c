/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:57:26 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 12:53:36 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_assign(char *arg, char ***envp)
{
	char	*new_var;
	char	*var_name;
	int		idx;
	int		name_len;

	new_var = ft_strdup(arg);
	if (!new_var)
		return (-1);
	var_name = extract_var_name(arg);
	if (!var_name)
	{
		free(new_var);
		return (-1);
	}
	name_len = ft_strlen(var_name);
	idx = find_var_index(*envp, var_name, name_len);
	free(var_name);
	if (idx != -1)
		return (update_existing(envp, idx, new_var));
	return (add_new_var(envp, new_var));
}

int	process_arg(char *arg, char ***envp, int type)
{
	char	*new_var;
	char	**new_env;

	new_env = NULL;
	if (type == CONCATENATION)
		return (process_concat(arg, envp));
	if (type == ASSIGNMENT)
		return (process_assign(arg, envp));
	new_var = ft_strdup(arg);
	if (!new_var)
		return (-1);
	return (declare_export(arg, envp, new_env, new_var));
}

int	builtin_export(char **args, char ***envp, t_exit *shell_state)
{
	int	identifier;
	int	i;

	if (!args[1])
		return (print_export(*envp, shell_state));
	i = 1;
	shell_state->exit_code = 0;
	while (args[i])
	{
		identifier = is_valid_identifier(args[i]);
		if (identifier == INVALID)
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
			shell_state->exit_code = 1;
			++i;
			continue ;
		}
		if (process_arg(args[i], envp, identifier) == -1)
		{
			shell_state->exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
