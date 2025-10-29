/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:32:32 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 11:10:40 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespaces(char *input, int *i)
{
	if (!input || !i)
		return ;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'
			|| input[*i] == '\n' || input[*i] == '\r' || input[*i] == '\v'
			|| input[*i] == '\f'))
		(*i)++;
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit((unsigned char)str[i++]))
			return (0);
	return (1);
}

int	is_valid_identifier(const char *str)
{
	int	i;
	int	type;

	i = 0;
	type = DECLARATION;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (INVALID);
	while (str[++i])
	{
		if (str[i] == '=')
		{
			type = ASSIGNMENT;
			if (i > 0 && str[i - 1] == '+')
				type = CONCATENATION;
			break ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (INVALID);
	}
	return (type);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	str_arr_len(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}
