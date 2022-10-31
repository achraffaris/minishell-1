/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:33:34 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/31 00:50:52 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_lexer	*init_lexer(char *contents, t_lexer *lexer)
{
	lexer->contents = contents;
	lexer->i = 0;
	lexer->flg = 1;
	lexer->c = contents[lexer->i];
	lexer->flg_error = 0;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_back(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i -= 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_space(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n')
	{
		lexer_advance(lexer);
	}
}

void	error_rdr(t_lexer *lexer)
{
	while (1)
	{
		if (lexer->c != '>' && lexer->c != '<')
			break ;
		lexer_advance(lexer);
	}
	lexer->flg_error = 1;
}
