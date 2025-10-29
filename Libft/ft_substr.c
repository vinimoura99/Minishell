/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:15:17 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/09 12:47:09 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*og;
	size_t	size;

	size = ft_strlen(s);
	if (len > size)
		len = size;
	if (size <= start || size == 0)
		len = 0;
	if (len > size - start)
		len = size - start;
	if (s == NULL)
		return (NULL);
	s += start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	og = str;
	while (len-- && *s != '\0')
		*str++ = *s++;
	*str = '\0';
	return (og);
}

/* int	main(void)
{
	char	*str = ft_substr("I am only testing", 2, 7);

	printf("%s", str);
} */
