/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:43:56 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 11:38:55 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_token *start)
{
	int	i;

	i = 0;
	if (!start)
		return (-1);
	while (start->type != TOKEN_EOF)
	{
		if (start->type == PIPE)
			++i;
		start = start->next;
	}
	return (i);
}

int	redir_counter(t_token *current)
{
	int	i;

	i = 0;
	while (current->type != PIPE && current->type != TOKEN_EOF)
	{
		if (current->type >= REDIR_IN && current->type <= REDIR_HEREDOC)
			++i;
		current = current->next;
	}
	return (i);
}

t_node	*create_cmd_node(t_token **current, int args_count, int type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = create_cmd(current, args_count, type, redir_counter(*current));
	if (node->cmd->redir->redir_count > 0)
		node->type = 'R';
	else
		node->type = 'C';
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*create_pipe_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = 'P';
	node->left = NULL;
	node->right = NULL;
	init_cmd(&node->cmd, 0);
	node->cmd->type = 0;
	return (node);
}

void	assign_root_parent(t_node *node, t_node *root)
{
	if (!node)
		return ;
	node->parent = root;
	assign_root_parent(node->left, root);
	assign_root_parent(node->right, root);
}
