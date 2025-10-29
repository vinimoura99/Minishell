/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:14:42 by joao-vri          #+#    #+#             */
/*   Updated: 2024/04/24 15:43:48 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (src[i] != '\0' && i < n - 1)
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/* int	main(void)
{
	size_t n = 4;
	char	*src = "hello";
	char	dst[10] = "world";
	size_t	i;

	i = ft_strlcpy(dst, src, n);
	ft_strlcpy(dst, src, n);
	printf("%s\n", dst);
	printf("%zu", i);
}*/
