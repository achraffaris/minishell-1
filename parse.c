/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:19:30 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/24 01:42:39 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_arg(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->e_type == 2)
			break ;
		else if (head->e_type == 1)
			i++;
			head = head->next;
	}
	return (i);
}

void	add_back_parse(t_parse **parse, t_parse *tmp)
{
	t_parse	*head;

	if (*parse == NULL)
		*parse = tmp;
	else
	{
		head = *parse;
		while (head->next)
			head = head->next;
		head->next = tmp;
	}
}

t_rdr	*add_rdr(char *str, int type, int herdoc)
{
	t_rdr	*rdr;

	rdr = malloc(sizeof(t_rdr));
	rdr->value = ft_strdup(str);
	rdr->type = type;
	rdr->herdoc = herdoc;
	rdr->next = NULL;
	return (rdr);
}

void	add_back_rdr(t_rdr **rdr, t_rdr *tmp)
{
	t_rdr	*head;

	if (*rdr == NULL)
		(*rdr) = tmp;
	else
	{
		head = *rdr;
		while (head->next != NULL)
			head = head->next;
		head->next = tmp;
	}
}
