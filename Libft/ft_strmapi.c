/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:15:19 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/14 13:37:46 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		++i;
	}
	str[i] = '\0';
	return (str);
}

/* char	ft_lowercase(unsigned int i, char str)
{
	if (str >= 'A' && str <= 'Z')
		str += 32;
	return (str);
}

int	main(void)
{
	char	str[10] = "HELLO";
	char	*dest = ft_strmapi(str, ft_lowercase);
	printf("%s", dest);
	free (dest);
} */
