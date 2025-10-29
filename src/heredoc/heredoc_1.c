/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:08:08 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 17:06:09 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_fd_open(int fd)
{
	char	c;
	ssize_t	ret;

	ret = read(fd, &c, 0);
	if (ret == -1 && errno == EBADF)
		return (0);
	return (1);
}

static int	handle_eof(int pipe_fd[], char *line,
		const char *del, t_exit *exit_code)
{
	char	*msg[2];
	int		fd;

	if (!is_fd_open(STDIN_FILENO))
	{
		fd = open("/dev/tty", O_RDONLY);
		if (fd >= 0 && fd != STDIN_FILENO)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		write(STDOUT_FILENO, "\n", 1);
		exit_code->exit_code = -5;
	}
	else
	{
		msg[0] = "minishell: warning: here-document";
		msg[1] = " delimited by end-of-file (wanted `";
		write(STDERR_FILENO, msg[0], ft_strlen(msg[0]));
		write(STDERR_FILENO, msg[1], ft_strlen(msg[1]));
		write(STDERR_FILENO, del, ft_strlen(del));
		write(STDERR_FILENO, "')\n", 3);
		free(line);
	}
	return (close(pipe_fd[1]), pipe_fd[0]);
}

static int	handle_delimiter(int pipe_fd[], char *line)
{
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static void	write_line(int fd, char *line, t_heredoc_data *data)
{
	char	*expanded;
	char	*line_copy;

	if (!data->quoted)
	{
		line_copy = ft_strdup(line);
		if (!line_copy)
			return ;
		if (line_copy)
		{
			expanded = expand_var(line_copy, data->env, data->exit_code, 1);
			write(fd, expanded, ft_strlen(expanded));
			if (expanded != line_copy)
				free(expanded);
			else if (line_copy)
				free(line_copy);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	heredoc(const char *del, int quoted, char **env, t_exit *exit_code)
{
	char			*line;
	int				pipe_fd[2];
	t_heredoc_data	data;

	data.env = env;
	data.exit_code = *exit_code;
	data.quoted = quoted;
	setup_signals_heredoc();
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (handle_eof(pipe_fd, line, del, exit_code));
		if (ft_strcmp(line, del) == 0)
			return (handle_delimiter(pipe_fd, line));
		write_line(pipe_fd[1], line, &data);
		free(line);
	}
}
