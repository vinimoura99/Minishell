/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:15:00 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/20 12:06:05 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_tree_data(t_token *tokens, t_cmd_info *info)
{
	info->pipe_count = count_pipes(tokens);
	define_cmd(tokens, info->pipe_count + 1, &info->args_count, &info->types);
}

static t_node	*update_tree_with_cmd(t_node *root, t_node *cmd_node,
		int env_og_size)
{
	t_node	*pipe_node;

	if (!root)
		return (cmd_node);
	pipe_node = create_pipe_node();
	pipe_node->left = root;
	pipe_node->right = cmd_node;
	pipe_node->env_og_size = env_og_size;
	return (pipe_node);
}

static t_node	*construct_tree(t_token *tokens, t_cmd_info *info,
		int env_og_size)
{
	t_token	*current;
	t_node	*root;
	t_node	*cmd_node;
	int		i;

	root = NULL;
	current = tokens;
	i = 0;
	while (i < info->pipe_count + 1)
	{
		cmd_node = create_cmd_node(&current, info->args_count[i],
				info->types[i]);
		cmd_node->env_og_size = env_og_size;
		root = update_tree_with_cmd(root, cmd_node, env_og_size);
		++i;
	}
	return (root);
}

t_node	*build_tree(t_token *tokens, int env_og_size)
{
	t_cmd_info	info;
	t_node		*root;

	if (!tokens)
		return (NULL);
	info.args_count = NULL;
	info.types = NULL;
	initialize_tree_data(tokens, &info);
	root = construct_tree(tokens, &info, env_og_size);
	if (info.args_count)
		free(info.args_count);
	if (info.types)
		free(info.types);
	assign_root_parent(root, root);
	return (root);
}
