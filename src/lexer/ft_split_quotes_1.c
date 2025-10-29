/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:49:26 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/22 14:22:28 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_untilnext_q(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] && !is_whitespace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

size_t	ft_skip_quoted(const char *str, size_t i)
{
	char	quote;

	while (str[i] && !is_whitespace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

char	**ft_alloc_word(char **strs, const char **s, size_t i)
{
	size_t	len;

	while (**s && is_whitespace(**s))
		(*s)++;
	len = ft_untilnext_q(*s);
	strs[i] = malloc(len + 1);
	if (!strs[i])
		return (ft_free_array(&strs));
	ft_strlcpy(strs[i], *s, len + 1);
	*s += len;
	return (strs);
}

char	**ft_split_quoted(char const *s)
{
	size_t	i;
	size_t	count;
	char	**strs;

	count = ft_strcount_q(s);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < count)
	{
		strs = ft_alloc_word(strs, &s, i);
		if (!strs)
			return (NULL);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
