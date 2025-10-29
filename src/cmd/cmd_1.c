/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:11:43 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 12:14:56 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_token **current, int args_count, int type,
		int redir_count)
{
	t_cmd	*cmd;
	int		i;
	int		n;

	n = 0;
	i = 0;
	if (initialize_command(&cmd, args_count, redir_count) == -1)
		return (NULL);
	cmd->type = type;
	while ((*current)->type != PIPE && (*current)->type != TOKEN_EOF)
		process_token(current, cmd, &i, &n);
	if (!cmd->cmd)
		cmd->cmd = NULL;
	if (args_count != 0)
		cmd->args[args_count] = NULL;
	jump_next_cmd(current);
	return (cmd);
}

int	initialize_command(t_cmd **cmd, int args_count, int redir_count)
{
	if (init_cmd(cmd, args_count) == -1)
		return (-1);
	if (init_redir(&(*cmd)->redir, redir_count) == -1)
		return (-1);
	return (0);
}

void	process_token(t_token **current, t_cmd *cmd, int *i, int *n)
{
	if ((*current)->type >= REDIR_IN && (*current)->type <= REDIR_HEREDOC)
		define_redir(current, &cmd->redir, n);
	else
	{
		if (!cmd->cmd && (*current)->type == ARGUMENT)
			cmd->cmd = ft_strdup((*current)->str);
		cmd->args[(*i)++] = ft_strdup((*current)->str);
	}
	(*current) = (*current)->next;
}

int	allocate_cmd_arrays(int cmd_count, int ***args_count, int ***types)
{
	(**args_count) = malloc(sizeof(int) * cmd_count);
	(**types) = malloc(sizeof(int) * cmd_count);
	if (!(**types) || !(**args_count))
		return (-1);
	return (0);
}
