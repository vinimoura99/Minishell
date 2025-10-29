/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:51 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/07 11:58:21 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ptr1;
	const char	*ptr2;

	ptr1 = (const char *)s1;
	ptr2 = (const char *)s2;
	while (n-- > 0)
	{
		if (*ptr1 != *ptr2)
			return ((unsigned char)*ptr1 - (unsigned char)*ptr2);
		++ptr1;
		++ptr2;
	}
	return (0);
}
/* int	main(void)
{
	printf("%i", ft_memcmp("TeSte", "TestE", 5));
} */
