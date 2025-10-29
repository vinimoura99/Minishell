/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:08:15 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 17:46:25 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_spaces_around_redirs(char *input, int *i)
{
	if (*i > 0 && !is_whitespace(input[*i - 1]))
		input = str_add_at(input, ' ', (*i)++);
	if (input[*i + 1] == '>' || input[*i + 1] == '<')
		(*i)++;
	(*i)++;
	if (input[*i] && !is_whitespace(input[*i]))
		input = str_add_at(input, ' ', *i);
	return (input);
}

char	*separate_redirs(char *input)
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
		else if ((input[i] == '<' || input[i] == '>') && !in_single
			&& !in_double)
			input = add_spaces_around_redirs(input, &i);
		i++;
	}
	return (input);
}

static int	check_pipe_syntax(char *input, int *i)
{
	(*i)++;
	skip_whitespaces(input, i);
	if (!input[*i] || input[*i] == '|')
		return (-1);
	return (0);
}

static int	check_first_pipe(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	skip_whitespaces(input, &i);
	if (input[i] == '|')
		return (0);
	return (1);
}

int	check_pipes(char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!input || !check_first_pipe(input))
		return (-1);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		else if (input[i] == '|' && !in_single && !in_double)
		{
			if (check_pipe_syntax(input, &i) == -1)
				return (-1);
			continue ;
		}
		i++;
	}
	return (0);
}
