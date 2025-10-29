/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:48:18 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/13 16:48:19 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/* int	main(void)
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("Hello ");
	t_list *node2 = ft_lstnew("World ");
	size_t	i;

	ft_lstadd_front(&lst, node1);
	node1->next = node2;
	node2->next = node1;

	i = 0;
	while(lst && i++ < 30)
	{
		printf("%s", (char *)lst->next->content);
		printf("%s", (char *)lst->next->next->content);
		printf("%s", (char *)lst->next->next->next->content);
	}
	free(node1);
	free(node2);
} */
