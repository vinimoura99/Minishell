/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:21:38 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/09 12:14:34 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c %= 256;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/* int	main(void)
{
	printf("%s", ft_strchr("Testete", 't'));
} */
