/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:44:56 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/15 14:31:43 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			free(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/* void	*ft_lowercase(void *content)
{
	size_t	i;
	char	*str;

	str = (char *)content;
	i = 0;
	while(str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (content);
}

void	del(void *content)
{
	if (content)
		free(content);
}

int	main(void)
{
	t_list	*lst;
	t_list	*node1;
	t_list	*node2;
	t_list	*map_lst;

	lst = NULL;
	node1 = ft_lstnew(ft_strdup("TESTE1"));
	node2 = ft_lstnew(ft_strdup("TESTE2"));

	ft_lstadd_front(&lst, node1);
	ft_lstadd_back(&lst, node2);

	map_lst = ft_lstmap(lst, (void *)ft_lowercase, del);
	printf("%s\n", (char *)map_lst->content);
	map_lst = map_lst->next;
	printf("%s\n", (char *)map_lst->content);
} */
