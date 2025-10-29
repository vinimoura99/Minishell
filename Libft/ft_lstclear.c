/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:15:39 by joao-vri          #+#    #+#             */
/*   Updated: 2024/05/13 18:37:28 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_next;

	if (lst && del)
	{
		while (*lst)
		{
			temp_next = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = temp_next;
		}
	}
}
