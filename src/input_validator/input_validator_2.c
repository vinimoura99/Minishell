/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:36:39 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 19:37:46 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_validator(char *input)
{
	int	quotes_error;

	if (!input)
		return (-1);
	quotes_error = check_quotes(input);
	if (check_redirs(input) == -1)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token\n", 46);
		return (-1);
	}
	else if (quotes_error == -1 || quotes_error == -2)
		return (handle_quotes_error(quotes_error));
	else if (check_pipes(input) == -1)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n", 50);
		return (-1);
	}
	else
		return (0);
}

int	handle_quotes_error(int quotes_error)
{
	write(STDERR_FILENO,
		"minishell: line 1: unexpected EOF while looking for matching `", 62);
	if (quotes_error == -1)
		write(STDERR_FILENO, "'", 1);
	else
		write(STDERR_FILENO, "\"", 1);
	write(STDERR_FILENO, "'\n", 2);
	return (-1);
}

int	check_quotes(char *input)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	if (!input)
		return (-1);
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		++i;
	}
	if (in_single)
		return (-1);
	else if (in_double)
		return (-2);
	return (0);
}

static int	check_redir_syntax(char *input, int *i)
{
	char	redir;

	redir = input[*i];
	if (redir == '<' && input[*i + 1] == '<' && input[*i + 2] == '<')
		return (-1);
	else if (redir == '>' && input[*i + 1] == '>' && input[*i + 2] == '>')
		return (-1);
	(*i)++;
	if (input[*i] == redir)
		(*i)++;
	skip_whitespaces(input, i);
	if (!input[*i] || input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
		return (-1);
	return (0);
}

int	check_redirs(char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!input)
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
		else if (!in_single && !in_double && (input[i] == '<'
				|| input[i] == '>'))
		{
			if (check_redir_syntax(input, &i) == -1)
				return (-1);
			continue ;
		}
		i++;
	}
	return (0);
}
