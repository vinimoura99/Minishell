/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:50:23 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 10:42:41 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_exit *shell_state)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write(STDERR_FILENO, "pwd: error retrieving current directory: ", 41);
		perror("getcwd: cannot access parent directories");
		shell_state->exit_code = 1;
		return (1);
	}
	printf("%s\n", cwd);
	shell_state->exit_code = 0;
	return (0);
}
