/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:19:30 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/17 00:16:33 by schoukou         ###   ########.fr       */
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

t_rdr	*add_rdr(char *str, int type)
{
	t_rdr	*rdr;

	rdr = malloc(sizeof(t_rdr));
	rdr->value = ft_strdup(str);
	rdr->type = type;
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

t_parse	*init_parsing(t_token **token, t_lexer *lexer)
{
	t_token	*head;
	t_parse	*tmp;
	t_parse	*parse;
	t_rdr	*rdr;
	int		i;

	parse = NULL;
	head = *token;
	tmp = malloc(sizeof(t_parse));
	tmp->arg = NULL;
	tmp->cmd = NULL;
	tmp->rdr = NULL;
	tmp->next = NULL;
	i = 0;
	while (head)
	{
		if (head->e_type == 2 && head->next != NULL && head->next->e_type == 2)
			lexer->flg_error = 1;
		if (head->e_type == 0)
			tmp->cmd = ft_strdup(head->value);
		else if (head->e_type == 1)
		{
			if (!tmp->arg)
			{
				tmp->arg = malloc(sizeof(char *) * (count_arg(head) + 1));
				i = 0;
			}
			tmp->arg[i] = ft_strdup(head->value);
			tmp->arg[++i] = NULL;
		}
		else if (head->e_type == 4 || head->e_type == 5 || head->e_type == 6 || head->e_type == 3)
		{
			rdr = add_rdr(head->value, head->e_type);
			add_back_rdr(&tmp->rdr, rdr);
		}
		else if (head->e_type == 2)
		{
			add_back_parse(&parse, tmp);
			tmp = malloc(sizeof(t_parse));
			tmp->next = NULL;
			tmp->rdr = NULL;
			tmp->arg = NULL;
		}
		head = head->next;
	}
	add_back_parse(&parse, tmp);
	return (parse);
}
