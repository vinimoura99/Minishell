/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:01:40 by joao-vri          #+#    #+#             */
/*   Updated: 2024/04/24 15:30:58 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

/*int main(void){
	int a = ft_isalnum('A');
	int b = ft_isalnum('c');
	int c = ft_isalnum('1');

	printf("%i\n", a);
	printf("%i\n", b);
	printf("%i\n", c);
	printf("%i", ft_isalnum('@'));
}*/
