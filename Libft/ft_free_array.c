/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:00:56 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/22 13:50:55 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ---------ADDITIONAL FUNCTION--------- */

void	*ft_free_array(char ***strs)
{
	size_t	i;

	if (!strs || !*strs)
		return (NULL);
	i = 0;
	while ((*strs)[i])
	{
		free((*strs)[i]);
		(*strs)[i] = NULL;
		++i;
	}
	free(*strs);
	*strs = NULL;
	return (NULL);
}
