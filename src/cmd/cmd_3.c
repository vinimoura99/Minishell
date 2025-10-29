/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:06:57 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/20 12:06:05 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*find_first_arg(t_token *start)
{
	if (start->type == PIPE)
		start = start->next;
	while (start->type != TOKEN_EOF && start->type != PIPE
		&& start->type != ARGUMENT)
	{
		if (start->type >= REDIR_IN && start->type <= REDIR_HEREDOC)
			start = start->next;
		start = start->next;
	}
	return (start);
}

static int	count_args(t_token **start, int *builtin_flag, int *assignment_flag)
{
	t_token	*current;
	int		n;

	current = *start;
	*builtin_flag = is_builtin(current->str);
	*assignment_flag = is_assignment(current->str);
	n = 0;
	while (current && (current->type != PIPE && current->type != TOKEN_EOF))
	{
		if (current->type == ARGUMENT)
			++n;
		while (current->type >= REDIR_IN && current->type <= REDIR_HEREDOC)
			current = current->next;
		current = current->next;
	}
	*start = current;
	return (n);
}

void	define_cmd(t_token *start, int cmd_count, int **args_count, int **types)
{
	int	i;
	int	builtin_flag;
	int	assignment_flag;
	int	arg_count;

	if (allocate_cmd_arrays(cmd_count, &args_count, &types) == -1 || !start)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		start = find_first_arg(start);
		arg_count = count_args(&start, &builtin_flag, &assignment_flag);
		define_cmd_type(builtin_flag, assignment_flag, &((*types)[i]));
		(*args_count)[i] = arg_count;
		++i;
	}
}

void	define_redir(t_token **current, t_redir **redir, int *n)
{
	if (!current)
		return ;
	(*redir)->redir_type[*n] = (int)(*current)->type;
	(*current) = (*current)->next;
	(*redir)->quotes[*n] = (int)(*current)->quote;
	(*redir)->args[*n] = ft_strdup((*current)->str);
	++(*n);
}
