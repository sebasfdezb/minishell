/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:58:31 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/13 11:27:28 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	void	*aux;

	if (!lst)
		return (0);
	new = 0;
	while (lst != NULL)
	{
		aux = f(lst->content);
		node = ft_lstnew(aux);
		if (node != NULL)
		{
			ft_lstadd_back(&new, node);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&new, del);
			del(aux);
			return (0);
		}
	}
	return (new);
}
