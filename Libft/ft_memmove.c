/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:45:14 by joao-vri          #+#    #+#             */
/*   Updated: 2024/04/26 13:41:37 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*ptr2;
	char		*ptr1;

	ptr2 = (const char *)src;
	ptr1 = (char *)dest;
	if (ptr1 == ptr2)
		return (dest);
	if (ptr1 < ptr2)
		while (n--)
			*ptr1++ = *ptr2++;
	else
	{
		ptr1 += n;
		ptr2 += n;
		while (n--)
			*(--ptr1) = *(--ptr2);
	}
	return (dest);
}

/* int	main(void)
{
	char	dest[50] = "Tes";
	char	src[50] = "Teste";
	ft_memmove(dest, src, 5);
	printf("%s", dest);
} */
