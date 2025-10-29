/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:29 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/09 12:29:51 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)str;
	c %= 256;
	while (n--)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}

/* int	main(void)
{
	char	*str = ft_memchr("Flamengo", 'm', 4);
	printf("%s", str);
} */
