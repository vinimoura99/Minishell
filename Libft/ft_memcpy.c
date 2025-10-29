/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:43:01 by joao-vri          #+#    #+#             */
/*   Updated: 2024/04/24 15:30:44 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*ptr2;
	char		*ptr1;

	ptr1 = dest;
	ptr2 = src;
	if (ptr1 == NULL && ptr2 == NULL)
		return (NULL);
	else
		while (n-- > 0)
			*ptr1++ = *ptr2++;
	return (dest);
}

/* int	main(void)
{
	char csrc[100] = "Teste123";
	ft_memcpy(csrc + 5, csrc, strlen(csrc) + 1);
	printf("%s", csrc);
	return (0);
} */
