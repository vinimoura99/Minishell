/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:12:22 by joao-vri          #+#    #+#             */
/*   Updated: 2024/09/09 13:42:09 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *src)
{
	int	i;
	int	signal;
	int	nbr;

	nbr = 0;
	signal = 1;
	i = 0;
	while ((src[i] >= 9 && src[i] <= 13) || (src[i] == 32))
		i++;
	if ((src[i] == '-') || (src[i] == '+'))
	{
		if (src[i] == '-')
			signal *= -signal;
		i++;
	}
	while (src[i] >= '0' && src[i] <= '9')
	{
		nbr = nbr * 10 + src[i] - 48;
		i++;
	}
	return (nbr * signal);
}

/* int	main(void)
{
	printf("%i", ft_atoi("\010 8"));
	printf("%i", atoi("\010 8"));
} */
