/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:13:59 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/19 13:17:08 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	if (g_exit_code)
		g_exit_code->exit_code = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals_shell(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_child_handler(int signo)
{
	(void)signo;
	if (g_exit_code)
		g_exit_code->exit_code = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc_handler(int signo)
{
	(void)signo;
	if (g_exit_code)
		g_exit_code->exit_code = 130;
	write(STDOUT_FILENO, "", 1);
	close(STDIN_FILENO);
}
