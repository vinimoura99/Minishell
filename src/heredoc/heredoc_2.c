/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:56:27 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 15:51:49 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredoc(t_redir **redir, char **env, t_exit *exit_code)
{
	int		i;
	int		*redir_type;
	char	**args;
	int		*quotes;

	i = 0;
	quotes = (*redir)->quotes;
	redir_type = (*redir)->redir_type;
	args = (*redir)->args;
	if (!(*redir)->heredoc_fd)
		return ;
	while (i < (*redir)->redir_count)
	{
		if (redir_type[i] == REDIR_HEREDOC)
			(*redir)->heredoc_fd[i] = heredoc(args[i], quotes[i], env,
					exit_code);
		++i;
	}
	setup_signals_shell();
}

void	process_all_heredocs(t_node *root, char **env, t_exit *exit_code)
{
	if (!root)
		return ;
	if (root->cmd && root->cmd->redir && root->cmd->redir->redir_count > 0
		&& root->cmd->redir->heredoc_fd && exit_code->exit_code != -5)
		process_heredoc(&root->cmd->redir, env, exit_code);
	if (root->left)
		process_all_heredocs(root->left, env, exit_code);
	if (root->right)
		process_all_heredocs(root->right, env, exit_code);
}
