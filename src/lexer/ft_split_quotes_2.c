/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:11:53 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/20 12:06:05 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	process_word(const char *str, size_t *i)
{
	char	quote;

	while (str[*i] && !is_whitespace(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (1);
}

size_t	ft_strcount_q(const char *str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		while (is_whitespace(str[i]))
			i++;
		if (str[i] != '\0')
			n += process_word(str, &i);
	}
	return (n);
}
