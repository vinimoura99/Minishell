/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:58:07 by joao-vri          #+#    #+#             */
/*   Updated: 2024/04/26 15:30:17 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
	return ;
}

/* int	main(void)
{
	ft_putstr_fd("Teste 123", 1);
} */
