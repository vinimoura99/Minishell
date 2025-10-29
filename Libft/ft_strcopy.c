/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:35:36 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/19 13:25:06 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	str_copy(char *new_str, char *str, char *str2, t_copy_params params)
{
	size_t	len_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < params.index)
		new_str[j++] = str[i++];
	i = 0;
	while (str2[i])
		new_str[j++] = str2[i++];
	len_str = ft_strlen(str);
	i = params.index + params.n;
	while (i < (int)len_str && str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
}
