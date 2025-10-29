/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:03:41 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 12:41:15 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out(char *arg)
{
	int	fd_out;

	fd_out = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open");
		return (1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	redir_append(char *arg)
{
	int	fd_out;

	fd_out = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror("open");
		return (1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	redir_in(char *arg)
{
	int	fd_in;

	fd_in = open(arg, O_RDONLY);
	if (fd_in == -1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

int	redir_heredoc(int fd)
{
	if (fd == -1)
	{
		write(1, "\n", 1);
		return (130);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	process_redirections(t_redir *redir, t_exit *exit_code)
{
	int		i;
	int		*redir_type;
	int		ret;
	char	**args;

	redir_type = redir->redir_type;
	args = redir->args;
	ret = 0;
	i = 0;
	while (i < redir->redir_count && ret != 1 && ret != 130)
	{
		if (redir_type[i] == REDIR_OUT)
			ret = redir_out(args[i]);
		else if (redir_type[i] == REDIR_APPEND)
			ret = redir_append(args[i]);
		else if (redir_type[i] == REDIR_IN)
			ret = redir_in(args[i]);
		else if (redir_type[i] == REDIR_HEREDOC)
			ret = redir_heredoc(redir->heredoc_fd[i]);
		i++;
	}
	exit_code->exit_code = ret;
	return (ret);
}
