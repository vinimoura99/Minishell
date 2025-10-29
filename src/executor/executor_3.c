/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:49:08 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 17:34:15 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(t_node *root, char ***env, t_exit *exit_code,
		int redir)
{
	t_node	*subtree;

	signal(SIGQUIT, SIG_DFL);
	if (redir == 1 && process_redirections(root->cmd->redir, exit_code) != 0)
	{
		subtree = root->parent;
		ft_free_array(env);
		free_binary_tree(&subtree);
		exit(exit_code->exit_code);
	}
	execute_cmd(root, env, exit_code);
	subtree = root->parent;
	ft_free_array(env);
	free_binary_tree(&subtree);
	exit(exit_code->exit_code);
}

static void	handle_parent_process(pid_t pid, t_exit *exit_code)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		exit_code->exit_code = 128 + sig;
		if (sig == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}

int	execute_node(t_node *root, char ***env, t_exit *exit_code, int redir)
{
	pid_t	pid;

	signal(SIGINT, sigint_child_handler);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
		handle_child_process(root, env, exit_code, redir);
	else
		handle_parent_process(pid, exit_code);
	setup_signals_shell();
	return (0);
}
