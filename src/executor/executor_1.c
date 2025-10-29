/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:02:49 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/22 18:38:57 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_specific_builtin(t_node *root, char ***env, t_exit *exit_code)
{
	char	*cmd_str;
	int		result;

	cmd_str = root->cmd->cmd;
	if (ft_strcmp(cmd_str, "echo") == 0 && cmd_str[4] == '\0')
		builtin_echo(root->cmd->args, exit_code);
	else if (ft_strcmp(cmd_str, "cd") == 0 && cmd_str[2] == '\0')
		builtin_cd(root->cmd->args, exit_code, env);
	else if (ft_strcmp(cmd_str, "pwd") == 0 && cmd_str[3] == '\0')
		builtin_pwd(exit_code);
	else if (ft_strcmp(cmd_str, "export") == 0 && cmd_str[6] == '\0')
		builtin_export(root->cmd->args, env, exit_code);
	else if (ft_strcmp(cmd_str, "unset") == 0 && cmd_str[5] == '\0')
		builtin_unset(root->cmd->args, env, exit_code);
	else if (ft_strcmp(cmd_str, "env") == 0 && cmd_str[3] == '\0')
		builtin_env(*env, exit_code);
	else if (ft_strcmp(cmd_str, "exit") == 0 && cmd_str[4] == '\0')
	{
		result = builtin_exit(root, *env, *exit_code);
		if (result >= 0)
			exit_code->exit_code = result;
		return (result);
	}
	return (0);
}

int	execute_builtin(t_node *root, char ***env, t_exit *exit_code, int redir)
{
	int	result;

	if (root->cmd == NULL || root->cmd->type != CMD_BUILT_IN)
		return (-2);
	if (redir == 1 && process_redirections(root->cmd->redir, exit_code) != 0)
		return (1);
	result = exec_specific_builtin(root, env, exit_code);
	if (result != 0 || ft_strcmp(root->cmd->cmd, "exit") == 0)
		return (result);
	return (exit_code->exit_code);
}

int	execute_cmd(t_node *root, char ***env, t_exit *exit_code)
{
	char	*path;

	path = get_path(root->cmd->cmd, *env);
	if (root->cmd->type == CMD_BUILT_IN)
		execute_builtin(root, env, exit_code, 0);
	else
		execute_external(path, root, exit_code, *env);
	free(path);
	return (exit_code->exit_code);
}

int	execute_tree(t_node *root, char ***env, t_exit *exit_code)
{
	if (!root)
		return (0);
	if (root->type == 'P')
		return (execute_pipe(root, env, exit_code));
	if (root->left)
		execute_tree(root->left, env, exit_code);
	if (root->right)
		execute_tree(root->right, env, exit_code);
	if (root->type == 'R')
		execute_node(root, env, exit_code, 1);
	else if (root->type == 'C')
		execute_node(root, env, exit_code, 0);
	return (0);
}

int	execute_pipe(t_node *node, char ***env, t_exit *exit_code)
{
	int		status;
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	signal(SIGINT, sigint_child_handler);
	left_pid = fork();
	if (left_pid == 0)
		send_left_node(node, pipe_fd, env, exit_code);
	right_pid = fork();
	if (right_pid == 0)
		send_right_node(node, pipe_fd, env, exit_code);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	setup_signals_shell();
	exit_code->exit_code = WEXITSTATUS(status);
	return (0);
}
