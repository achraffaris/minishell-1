/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:52:39 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/24 01:45:20 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*init_token(int type, char *value, t_lexer *lexer)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->value = malloc(sizeof(char) * (ft_strlen(value) + 1));
	token->e_type = type;
	token->value = value;
	token->next = NULL;
	token->rdr_flg = 0;
	if (lexer->flg_error == 0)
		token->rdr_flg = 1;
	return (token);
}
