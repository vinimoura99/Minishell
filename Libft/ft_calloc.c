/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:54:59 by joao-vri          #+#    #+#             */
/*   Updated: 2024/04/24 15:31:19 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(size * nmemb);
	if (ptr != NULL)
	{
		ft_memset(ptr, 0, size * nmemb);
		return (ptr);
	}
	return (NULL);
}

/* int	main(void)
{
	char	*str1 = (char*)ft_calloc(12, sizeof(char));
	char	str2[12] = "Teste";

	ft_strcpy(str1, str2);
	printf("%s", str1);

	free(str1);
	return (0);
} */
