/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:25:01 by afaris            #+#    #+#             */
/*   Updated: 2021/11/24 18:05:30 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_head;

	new = malloc(sizeof(t_list));
	if (!new || !lst)
		return (NULL);
	new_head = new;
	while (lst -> next)
	{
		new -> next = malloc(sizeof(t_list));
		if (!new -> next)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		new -> content = f(lst -> content);
		new = new -> next;
		lst = lst -> next;
	}
	new -> content = f(lst -> content);
	new -> next = NULL;
	return (new_head);
}
