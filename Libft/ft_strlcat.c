/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:49:29 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/06 14:56:49 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= size)
		return (size + len_src);
	while (src[i] != '\0' && len_dst + i < size - 1)
	{
		dst[len_dst + i] = src[i];
		++i;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

/* int	main(void)
{
	char dst[10] = "a";
	const char *src = "lorem ipsum dolor sit amet";
	size_t size = 0;

	printf("%lu\n", ft_strlcat(dst, src, size));
	ft_strlcat(dst, src, size);
	printf("%s", dst);
} */
