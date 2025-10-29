/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:37:36 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/14 14:16:53 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* void	ft_lowercase(void *str)
{
	char	*s;

	s = (char *)str;
	while (*s)
	{
		if (*s >= 'A' && *s <= 'Z')
			*s += 32;
		++s;
	}
}

int	main(void)
{
	t_list	*lst;
	t_list	*node1;
	t_list	*node2;

	lst = NULL;
	node1 = ft_lstnew(ft_strdup("TESTE1"));
	node2 = ft_lstnew(ft_strdup("TESTE2"));

	ft_lstadd_front(&lst, node1);
	ft_lstadd_back(&lst, node2);
	ft_lstiter(lst, ft_lowercase);
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
} */
