/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:27:35 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/10 17:26:41 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_token *start)
{
	int		count;
	t_token	*prev;

	count = 0;
	prev = NULL;
	while (start->type != TOKEN_EOF)
	{
		if (start->type == ARGUMENT && (!prev || prev->type == PIPE))
		{
			count++;
			while (start && start->type == ARGUMENT)
				start = start->next;
		}
		else
		{
			prev = start;
			start = start->next;
		}
	}
	return (count);
}

void	define_cmd_type(int is_builtin_flag, int is_assignment_flag, int *types)
{
	if (!types)
		return ;
	if (is_assignment_flag == CMD_ASSIGNMENT)
		(*types) = CMD_ASSIGNMENT;
	else if (is_builtin_flag == CMD_BUILT_IN)
		(*types) = CMD_BUILT_IN;
	else
		(*types) = CMD_EXTERNAL;
}

int	is_assignment(char *str)
{
	int	i;

	if (!str || !((str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z') || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (0);
		i++;
	}
	if (str[i] == '=')
		return (CMD_ASSIGNMENT);
	return (0);
}

int	is_builtin(char *arg)
{
	if (arg == NULL)
		return (0);
	if (ft_strcmp(arg, "echo") == 0 && arg[4] == '\0')
		return (CMD_BUILT_IN);
	else if (ft_strcmp(arg, "cd") == 0 && arg[2] == '\0')
		return (CMD_BUILT_IN);
	else if (ft_strcmp(arg, "pwd") == 0 && arg[3] == '\0')
		return (CMD_BUILT_IN);
	else if (ft_strcmp(arg, "export") == 0 && arg[6] == '\0')
		return (CMD_BUILT_IN);
	else if (ft_strcmp(arg, "unset") == 0 && arg[5] == '\0')
		return (CMD_BUILT_IN);
	else if (ft_strcmp(arg, "env") == 0 && arg[3] == '\0')
		return (CMD_BUILT_IN);
	else if (ft_strcmp(arg, "exit") == 0 && arg[4] == '\0')
		return (CMD_BUILT_IN);
	return (0);
}

void	jump_next_cmd(t_token **current)
{
	if (!current)
		return ;
	while ((*current)->type != PIPE && (*current)->type != TOKEN_EOF)
		(*current) = (*current)->next;
	(*current) = (*current)->next;
}
