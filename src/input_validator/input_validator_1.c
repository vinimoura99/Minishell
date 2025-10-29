/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:27:56 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 13:08:37 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_input(char *input, char **env, t_exit exit_code)
{
	if (!input)
		return (NULL);
	input = expand_var(input, env, exit_code, 0);
	input = separate_pipe(input);
	input = separate_redirs(input);
	return (input);
}

char	*escape_backlash(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\\')
			input = str_add_at(input, '\\', i++);
		++i;
	}
	return (input);
}

static char	*add_spaces_around_pipe(char *input, int *i)
{
	if (*i > 0 && !is_whitespace(input[*i - 1]))
		input = str_add_at(input, ' ', (*i)++);
	(*i)++;
	if (input[*i] && !is_whitespace(input[*i]))
		input = str_add_at(input, ' ', *i);
	return (input);
}

char	*separate_pipe(char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		else if (input[i] == '|' && !in_single && !in_double)
			input = add_spaces_around_pipe(input, &i);
		i++;
	}
	return (input);
}
