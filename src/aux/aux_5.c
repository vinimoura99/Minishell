/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:09:00 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 17:20:02 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	define_color(char **envp)
{
	int	i;

	i = get_str_index(envp, "TERM=", 0);
	if (i == -1)
		return (0);
	if (ft_strcmp(envp[i], "TERM=xterm-256color"))
		return (0);
	i = get_str_index(envp, "COLORTERM=", 0);
	if (i == -1)
		return (0);
	if (ft_strcmp(envp[i], "COLORTERM=truecolor"))
		return (0);
	return (1);
}
