/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:54:16 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/13 16:49:12 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/* int	main(void)
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("Hello ");
	t_list *node2 = ft_lstnew("World ");
	size_t	i;

	ft_lstadd_front(&lst, node1);
	node1->next = node2;

	printf("%i", ft_lstsize(lst));
	free(node1);
	free(node2);
} */
