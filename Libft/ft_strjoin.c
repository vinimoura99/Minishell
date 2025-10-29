/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:04:46 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/09 12:48:42 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, len_s1 + len_s2);
	ft_strlcpy(str + len_s1, (char *)s2, len_s2);
	return (str);
}

/* int	main(void)
{
	char	str[12] = "dsafagdsgds";

	printf("%s", ft_strjoin(str, "12ds3"));
} */
