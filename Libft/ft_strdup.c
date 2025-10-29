/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:50:14 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/07 13:29:29 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(src);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (*src)
		*dup++ = *src++;
	*dup = '\0';
	dup -= len;
	return (dup);
}

/* int	main(int ac, char **av)
{
	ac = -ac;
	printf("%s", ft_strdup(av[1]));
} */
