/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:50:38 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/13 18:15:28 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/* int	main(void)
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("Hello World");

	lst = node1;
	printf("%s", (char *)lst->content);
} */
