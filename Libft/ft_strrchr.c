/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:54:29 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/09 12:23:51 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	c %= 256;
	while (*s)
	{
		if (*s == c)
			ptr = (char *)s;
		s++;
	}
	if (c == '\0')
	{
		ptr = (char *)s;
		return (ptr += ft_strlen(ptr));
	}
	return (ptr);
}

/* int main(void)
{
	printf("%s\n", ft_strrchr("Testete", 'a'));
	printf("%s", strrchr("Testete", 'a'));
} */
