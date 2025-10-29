/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:43:28 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/19 11:36:19 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args, t_exit *shell_state)
{
	int	i;
	int	print_n;

	i = 1;
	print_n = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		print_n = 1;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!print_n)
		write(1, "\n", 1);
	shell_state->exit_code = 0;
	return (0);
}
