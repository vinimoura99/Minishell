/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:18 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 18:28:47 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **envp, t_exit *shell_state)
{
	int	i;
	int	equal_sign;

	i = 0;
	equal_sign = 0;
	while (envp[i])
	{
		if (envp[i][0] != '-')
		{
			char_search(envp[i], "=", &equal_sign);
			if (equal_sign != -1)
				printf("%s\n", envp[i]);
		}
		equal_sign = 0;
		++i;
	}
	shell_state->exit_code = 0;
	return (0);
}
