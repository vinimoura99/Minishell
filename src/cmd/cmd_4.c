/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:07:24 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/20 12:06:05 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_cmd **new_cmd, int args_count)
{
	(*new_cmd) = malloc(sizeof(t_cmd));
	if (!(*new_cmd))
		return (-1);
	(*new_cmd)->cmd = NULL;
	(*new_cmd)->redir = malloc(sizeof(t_redir));
	if (!(*new_cmd)->redir)
		return (-1);
	(*new_cmd)->redir->redir_count = 0;
	(*new_cmd)->redir->redir_type = NULL;
	(*new_cmd)->redir->quotes = NULL;
	(*new_cmd)->redir->args = NULL;
	(*new_cmd)->redir->heredoc_fd = NULL;
	if (args_count != 0)
	{
		(*new_cmd)->args = malloc(sizeof(char *) * (args_count + 1));
		if (!(*new_cmd)->args)
			return (-1);
	}
	else
		(*new_cmd)->args = NULL;
	if (!new_cmd || !(*new_cmd)->redir)
		return (-1);
	return (0);
}

int	init_redir(t_redir **redir, int redir_count)
{
	(*redir)->redir_type = malloc(sizeof(int) * redir_count);
	if (!(*redir)->redir_type)
		return (-1);
	(*redir)->quotes = malloc(sizeof(int) * redir_count);
	if (!(*redir)->quotes)
		return (-1);
	(*redir)->args = malloc(sizeof(char *) * redir_count);
	if (!(*redir)->args)
		return (-1);
	(*redir)->heredoc_fd = malloc(sizeof(int) * redir_count);
	if (!(*redir)->heredoc_fd)
		return (-1);
	(*redir)->redir_count = redir_count;
	while (redir_count > 0)
	{
		(*redir)->heredoc_fd[redir_count - 1] = -1;
		redir_count--;
	}
	if (!(*redir)->redir_type || !(*redir)->quotes || !(*redir)->args)
		return (-1);
	return (0);
}
