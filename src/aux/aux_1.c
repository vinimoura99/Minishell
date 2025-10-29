/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:27:59 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/23 01:26:09 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_remove_at(char *str, int index)
{
	size_t	len;
	size_t	i;
	size_t	n;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (index < 0 || (size_t)index >= len)
		return (str);
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (str[i])
	{
		if ((int)i != index)
			new_str[n++] = str[i];
		i++;
	}
	new_str[n] = '\0';
	free(str);
	return (new_str);
}

char	*str_substitute(char *str, int index, int n, char *str2)
{
	size_t			len_str;
	size_t			new_len;
	char			*new_str;
	t_copy_params	params;

	if (!str || !str2 || index < 0 || n < 0)
		return (str);
	len_str = ft_strlen(str);
	if ((size_t)index >= len_str)
		return (str);
	if ((size_t)(index + n) > len_str)
		n = len_str - index;
	new_len = len_str - n + ft_strlen(str2);
	new_str = malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	params.index = index;
	params.n = n;
	str_copy(new_str, str, str2, params);
	return (new_str);
}

int	get_str_index(char **str, char *str_to_search, int check_unset)
{
	int	i;

	i = 0;
	if (!str || !(*str))
		return (-1);
	if (!str_to_search)
		return (-1);
	while (str[i] && ft_strncmp(str[i], str_to_search,
			ft_strlen(str_to_search) - 1))
		++i;
	if (!str[i] && check_unset != 0)
	{
		i = 0;
		while (str[i] && ft_strncmp(str[i] + 1, str_to_search,
				ft_strlen(str_to_search) - 1))
			++i;
	}
	if (!str[i])
		return (-1);
	return (i);
}

char	char_search(char *input, char *characters, int *start)
{
	int	i;

	i = 0;
	if (!input)
		return ('\0');
	while (input[*start])
	{
		while (characters[i])
		{
			if (input[*start] == characters[i])
				return (characters[i]);
			++i;
		}
		i = 0;
		(*start)++;
	}
	(*start) = -1;
	return ('\0');
}
