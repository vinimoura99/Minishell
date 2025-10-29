/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:51:22 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/03 15:37:08 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
		{
			f(i, &s[i]);
			++i;
		}
	}
}

/* void	ft_lowercase(unsigned int i, char *str)
{
	i = 0;
	if (str[i] >= 'A' && str[i] <= 'Z')
		str[i] += 32;
}

int	main(void)
{
	char	str[14] = "TEESTETESTE";

	ft_striteri(str, ft_lowercase);
	printf("%s", str);
} */
