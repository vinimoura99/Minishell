/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:48:38 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 20:22:24 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_outside_quotes(char ***input)
{
	int		len;
	int		i;
	char	*old_str;

	i = 0;
	while ((*input)[i] != NULL)
	{
		len = ft_strlen((*input)[i]);
		if ((len >= 2 && (((*input)[i][0] == '\'')
			&& ((*input)[i][len - 1] == '\'')))
			|| (len >= 2 && (((*input)[i][0] == '"')
			&& ((*input)[i][len - 1] == '"'))))
		{
			old_str = (*input)[i];
			(*input)[i] = ft_substr((*input)[i], 1, len - 2);
			free(old_str);
		}
		++i;
	}
}

static void	process_quote(char **str, int *n, int *in_single, int *in_double)
{
	if ((*str)[*n] == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
		*str = str_remove_at(*str, *n);
	}
	else if ((*str)[*n] == '"' && !(*in_single))
	{
		*in_double = !(*in_double);
		*str = str_remove_at(*str, *n);
	}
	else
		(*n)++;
}

void	clear_inside_quotes(char ***input, int *quotes)
{
	int	i;
	int	n;
	int	in_single;
	int	in_double;

	i = 0;
	while ((*input)[i] != NULL)
	{
		n = 0;
		in_single = (quotes[i] == 1);
		in_double = (quotes[i] == 2);
		while ((*input)[i][n] != '\0')
			process_quote(&(*input)[i], &n, &in_single, &in_double);
		++i;
	}
}
