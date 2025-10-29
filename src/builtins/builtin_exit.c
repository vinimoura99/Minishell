/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:51:39 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/24 15:43:45 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cleanup(char **env, t_node *root, int status)
{
	t_node	*subtree;

	subtree = root->parent;
	if (subtree == root)
		printf("exit\n");
	ft_free_array(&env);
	free_binary_tree(&subtree);
	rl_clear_history();
	exit(status);
}

static void	exit_invalid_arg(t_node *root, char **env, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_cleanup(env, root, 2);
}

int	builtin_exit(t_node *root, char **env, t_exit exit_code)
{
	long long	num;
	char		*endptr;

	if (!root->cmd->args[1] || (ft_strcmp(root->cmd->args[1], "--") == 0
			&& !root->cmd->args[2]))
	{
		exit_cleanup(env, root, exit_code.exit_code);
		return (-1);
	}
	errno = 0;
	num = ft_strtoll(root->cmd->args[1], &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE || errno == EINVAL)
	{
		exit_invalid_arg(root, env, root->cmd->args[1]);
		return (-1);
	}
	if (root->cmd->args[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_cleanup(env, root, num % 256);
	return (-1);
}
