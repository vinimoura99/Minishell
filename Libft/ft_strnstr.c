/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:18:01 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/10 10:20:36 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;

	if (!big && !len)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (*big && len--)
	{
		n = 0;
		while (*(big + n) == *(little + n) && *(little + n) && n <= len)
		{
			if (!*(little + n + 1))
				return ((char *)big);
			++n;
		}
		++big;
	}
	return (NULL);
}

/*int	main(void)
{
	printf("%s", ft_strnstr("Abctestestextestex", "t", 10));
}*/
