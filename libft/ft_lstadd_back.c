/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:27:09 by afaris            #+#    #+#             */
/*   Updated: 2021/11/24 18:11:08 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = (*lst);
	if ((*lst) == NULL)
		(*lst) = new;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = new;
	}
}

/*
void	print_list(t_list *list)ll
{
	while (list)
	{
		printf("%d-->", *(int *)list->content);
		list = list -> next;
	}
	printf("NULL\n");
}

int main()
{
	t_list	*head;
	t_list	new;

	t_list A, B, C;
//linking 
	head = &A;
	A.next = &B;
	B.next = &C;
	C.next = NULL;
	
// filling the content 
	int a, b, c, d;
	a = 1;
	b = 2;
	c = 3;
	d = 4;

	A.content = &a;
	B.content = &b;
	C.content = &c;
	new.content = &d;


	print_list(head);
	ft_lstadd_back(&head, &new);
	print_list(head);
	
	return 0;4444
}*/
