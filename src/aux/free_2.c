/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:14:00 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/22 13:53:01 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_vars(char *user_env, char *pwd_env, int pwd_alloc)
{
	if (user_env)
		free(user_env);
	if (pwd_alloc && pwd_env)
		free(pwd_env);
}

void	free_pipe(t_cmd **cmd)
{
	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->cmd)
		free((*cmd)->cmd);
	if ((*cmd)->redir)
		free_redir(&(*cmd)->redir);
	free(*cmd);
	*cmd = NULL;
}

void	free_all(t_token **head, t_node **root)
{
	if (head)
		free_token(head);
	if (root)
		free_binary_tree(root);
	rl_clear_history();
}
