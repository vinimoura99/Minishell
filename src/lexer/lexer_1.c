/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:25:46 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 20:18:39 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char *input, t_token **head, int input_count)
{
	char	**new_input;
	int		*types;
	int		*quotes;
	int		i;

	if (!input)
		return ;
	i = 0;
	new_input = ft_split_quoted(input);
	quotes = define_quote(new_input, input_count);
	clear_outside_quotes(&new_input);
	clear_inside_quotes(&new_input, quotes);
	types = define_type(new_input, input_count, quotes);
	while (new_input[i])
	{
		create_token(head, types[i], new_input[i], quotes[i]);
		++i;
	}
	create_token(head, types[i], "NULL", quotes[i]);
	free(types);
	free(quotes);
	free(input);
	ft_free_array(&new_input);
}

static int	get_token_type(char *input_token, int quote)
{
	if (quote != 0)
		return (ARGUMENT);
	if (ft_strcmp(input_token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(input_token, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(input_token, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(input_token, "<<") == 0)
		return (REDIR_HEREDOC);
	if (ft_strcmp(input_token, "<") == 0)
		return (REDIR_IN);
	return (ARGUMENT);
}

int	*define_type(char **input, int input_count, int *quotes)
{
	int	*types;
	int	i;

	types = malloc(sizeof(int) * input_count);
	if (!types)
		return (NULL);
	i = 0;
	while (input[i])
	{
		types[i] = get_token_type(input[i], quotes[i]);
		i++;
	}
	types[i] = TOKEN_EOF;
	return (types);
}

int	*define_quote(char **input, int input_count)
{
	int	*quotes;
	int	i;
	int	len;

	i = 0;
	quotes = (int *)malloc(sizeof(int) * (input_count));
	if (!quotes)
		return (NULL);
	while (input[i])
	{
		len = ft_strlen(input[i]);
		if (len >= 2 && input[i][0] == '\'' && input[i][len - 1] == '\'')
			quotes[i] = 1;
		else if (len >= 2 && input[i][0] == '"' && input[i][len - 1] == '"')
			quotes[i] = 2;
		else
			quotes[i] = 0;
		++i;
	}
	quotes[i] = 0;
	return (quotes);
}

void	create_token(t_token **head, char type, char *str, char quote)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->str = ft_strdup(str);
	new_token->type = type;
	new_token->quote = quote;
	if (*head == NULL)
	{
		new_token->next = new_token;
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next != *head)
			current = current->next;
		current->next = new_token;
		new_token->next = *head;
	}
}
