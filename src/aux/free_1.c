/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:10:39 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 11:13:09 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **head)
{
	t_token	*current;
	t_token	*temp;

	if ((*head) == NULL)
		return ;
	current = (*head)->next;
	while (current != (*head))
	{
		temp = current->next;
		free(current->str);
		free(current);
		current = NULL;
		current = temp;
	}
	free(current->str);
	free((*head));
	(*head) = NULL;
}

void	free_redir(t_redir **redir)
{
	int	i;

	if (!redir || !*redir)
		return ;
	if ((*redir)->heredoc_fd)
		free((*redir)->heredoc_fd);
	if ((*redir)->redir_type)
		free((*redir)->redir_type);
	if ((*redir)->quotes)
		free((*redir)->quotes);
	if ((*redir)->args)
	{
		i = 0;
		while (i < (*redir)->redir_count && (*redir)->args[i])
		{
			free((*redir)->args[i]);
			i++;
		}
		free((*redir)->args);
	}
	free(*redir);
	*redir = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->cmd)
		free((*cmd)->cmd);
	if ((*cmd)->args)
	{
		i = 0;
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			i++;
		}
		free((*cmd)->args);
	}
	if ((*cmd)->redir)
		free_redir(&(*cmd)->redir);
	free(*cmd);
	*cmd = NULL;
}

void	free_binary_tree(t_node **root)
{
	if (!root || !*root)
		return ;
	free_binary_tree(&(*root)->left);
	free_binary_tree(&(*root)->right);
	if ((*root)->cmd && ((*root)->type == 'C' || (*root)->type == 'R'))
		free_cmd(&(*root)->cmd);
	else
		free_pipe(&(*root)->cmd);
	free(*root);
	*root = NULL;
}

void	free_node(t_node **node)
{
	if (!node || !*node)
		return ;
	if ((*node)->cmd && ((*node)->type == 'C' || (*node)->type == 'R'))
		free_cmd(&(*node)->cmd);
	else
		free_pipe(&(*node)->cmd);
}
