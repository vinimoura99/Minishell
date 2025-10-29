/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:04:04 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/22 18:35:52 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_add_at(char *new_str, char *str, char to_add, int index)
{
	size_t	i;
	size_t	n;
	size_t	len;

	i = 0;
	n = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if ((int)n == index)
			new_str[n++] = to_add;
		else
			new_str[n++] = str[i++];
	}
	if ((size_t)index == len)
		new_str[n++] = to_add;
	new_str[n] = '\0';
}

char	*str_add_at(char *str, char to_add, int index)
{
	size_t	len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (index < 0 || (size_t)index > len)
		return (str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	fill_add_at(new_str, str, to_add, index);
	free(str);
	return (new_str);
}

char	**copy_str_array(char **arr, int size)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(arr[i]);
		i++;
	}
	copy[size] = NULL;
	return (copy);
}

char	**sorted_copy(char **arr)
{
	int		size;
	char	**copy;

	size = str_arr_len(arr);
	if (!arr || size <= 0)
		return (NULL);
	copy = copy_str_array(arr, size);
	if (!copy)
		return (NULL);
	bubble_sort(copy, 0, size);
	return (copy);
}

void	bubble_sort(char **arr, int start, int end)
{
	int	i;
	int	j;

	i = start;
	while (i < end - 1)
	{
		j = start;
		while (j < end - 1 - (i - start))
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}
