/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:13 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/06 17:45:09 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_digits(int n)
{
	int	dig;

	dig = 0;
	while (n <= -10 || n >= 10)
	{
		n /= 10;
		dig++;
	}
	if (n < 0)
		dig++;
	return (dig + 1);
}

char	*ft_minint(char *nbr)
{
	nbr = (char *)malloc(sizeof(char) * 12);
	if (!nbr)
		return (NULL);
	ft_strlcpy(nbr, "-2147483648", 12);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	size_t	dig;
	int		n_pos;

	n_pos = n;
	nbr = NULL;
	if (n == -2147483648)
		return (ft_minint(nbr));
	dig = ft_digits(n);
	if (n < 0)
		n_pos *= -1;
	nbr = (char *)malloc(sizeof(char) * (dig + 1));
	if (!nbr)
		return (NULL);
	*(nbr + dig) = 0;
	while (dig--)
	{
		*(nbr + dig) = n_pos % 10 + '0';
		n_pos = n_pos / 10;
	}
	if (n < 0)
		*nbr = '-';
	return (nbr);
}

/* int	main(void)
{
	char	*nbr = ft_itoa(-121);
	printf("%s", nbr);
	free (nbr);
} */
