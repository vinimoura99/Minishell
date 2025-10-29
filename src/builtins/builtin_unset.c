/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:03 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 18:29:50 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_match(char *env_var, char *arg, int var_len)
{
	return (ft_strncmp(env_var, arg, var_len) == 0 && (env_var[var_len] == '='
			|| env_var[var_len] == '\0'));
}

int	builtin_unset(char **args, char ***envp, t_exit *shell_state)
{
	int	i;
	int	n;
	int	var_len;

	n = 1;
	if (!args[1])
	{
		shell_state->exit_code = 0;
		return (0);
	}
	while (args[n])
	{
		i = 0;
		var_len = ft_strlen(args[n]);
		while ((*envp)[i])
		{
			if (check_var_match((*envp)[i], args[n], var_len))
				(*envp)[i] = str_add_at((*envp)[i], '-', 0);
			else
				i++;
		}
		n++;
	}
	shell_state->exit_code = 0;
	return (0);
}
