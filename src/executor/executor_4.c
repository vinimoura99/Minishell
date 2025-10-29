/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:49:53 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 16:35:10 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	send_left_node(t_node *node, int *pipe_fd, char ***env, t_exit *exit_code)
{
	t_node	*subtree;

	subtree = node->parent;
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_tree(node->left, env, exit_code);
	ft_free_array(env);
	free_binary_tree(&subtree);
	rl_clear_history();
	exit(exit_code->exit_code);
}

int	send_right_node(t_node *node, int *pipe_fd, char ***env, t_exit *exit_code)
{
	t_node	*subtree;

	subtree = node->parent;
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_tree(node->right, env, exit_code);
	ft_free_array(env);
	free_binary_tree(&subtree);
	rl_clear_history();
	exit(exit_code->exit_code);
}

void	execute_external(char *path, t_node *root, t_exit *exit_code,
		char **env)
{
	if (root->cmd->cmd == NULL)
		return ;
	if (!path)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, root->cmd->cmd, ft_strlen(root->cmd->cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit_code->exit_code = 127;
		return ;
	}
	execve(path, root->cmd->args, env);
	execve_error(root, path, exit_code);
}

int	execute_all(t_node *root, char ***env, t_exit *exit_code)
{
	int	ret;
	int	copy_stdin;
	int	copy_stdout;

	if (root->cmd->type == CMD_BUILT_IN && root->type != 'P')
	{
		if (root->type == 'R')
		{
			copy_stdin = dup(STDIN_FILENO);
			copy_stdout = dup(STDOUT_FILENO);
			ret = execute_builtin(root, env, exit_code, 1);
			dup2(copy_stdin, STDIN_FILENO);
			dup2(copy_stdout, STDOUT_FILENO);
			close(copy_stdin);
			close(copy_stdout);
		}
		else
			ret = execute_builtin(root, env, exit_code, 0);
	}
	else
		ret = execute_tree(root, env, exit_code);
	return (ret);
}

void	execve_error(t_node *root, char *path, t_exit *exit_code)
{
	struct stat	st;

	if ((errno == EACCES) && (stat(path, &st) == 0) && S_ISDIR(st.st_mode))
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, root->cmd->cmd, ft_strlen(root->cmd->cmd));
		write(STDERR_FILENO, ": Is a directory\n", 17);
		exit_code->exit_code = 126;
	}
	else
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, root->cmd->cmd, ft_strlen(root->cmd->cmd));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		if (errno == EACCES || errno == EISDIR)
			exit_code->exit_code = 126;
		else if (errno == ENOENT)
			exit_code->exit_code = 127;
		else
			exit_code->exit_code = 1;
	}
}
