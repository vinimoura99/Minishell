/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:33:59 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/13 16:48:50 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

/* int	main(void)
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("Hello ");
	t_list *node2 = ft_lstnew("World ");

	ft_lstadd_front(&lst, node2);
	ft_lstadd_front(&lst, node1);
	node1->next = node2;

	printf("%s", (char *)(ft_lstlast(lst))->content);
	free(node1);
	free(node2);
} */
