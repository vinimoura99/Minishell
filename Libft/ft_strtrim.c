/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:03 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/21 15:55:15 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	n;
	char	*str;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	n = ft_strlen(s1);
	while (n && ft_strchr(set, s1[n - 1]))
		n--;
	str = malloc(n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}

/* int	main(void)
{
	char	*str;

	str = ft_strtrim("    a    Teste123    a    ", "a ");
	printf("%s", str);
	free(str);
} */
