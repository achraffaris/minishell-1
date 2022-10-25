/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:39:53 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/23 21:41:21 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*get_next_token3(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		lexer_advance(lexer);
		if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_DRRD,
						get_current_char_as_string_redirection(lexer), lexer)));
		else if (lexer->c != '<' && lexer->c != '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SRRD,
						get_current_char_as_string_redirection(lexer), lexer)));
		else
			error_rdr(lexer);
	}
	else if (lexer->c == '<')
	{
		lexer_advance(lexer);
		if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_HERDOC,
						get_current_char_as_string_redirection(lexer), lexer)));
		else if (lexer->c != '<' && lexer->c != '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SLRD,
						get_current_char_as_string_redirection(lexer), lexer)));
		else
			error_rdr(lexer);
	}
	return (NULL);
}

t_token	*get_next_token2(t_lexer *lexer)
{
	if (lexer->c == '\'')
		return (handle_single_quote(lexer));
	else if (lexer->c == '"')
		return (handle_single_quote(lexer));
	else if (lexer->c == '|')
		return (collect_pipe(lexer));
	else if (lexer->c == '<' || lexer->c == '>')
		return (get_next_token3(lexer));
	else if (lexer->c == '$')
		return (init_token(TOKEN_ENV,
				get_current_char_as_string_2(lexer), lexer));
	return (NULL);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ')
			lexer_skip_space(lexer);
		else if (lexer->c != '>' && lexer->c != '|'
			&& lexer->c != '<' && lexer->flg == 1)
		{
			lexer->flg = 0;
			return (init_token(TOKEN_CMD, collect_string(lexer), lexer));
		}
		else if (lexer->c != '>' && lexer->c != '|'
			&& lexer->c != '<' && lexer->flg == 0)
			return (init_token(TOKEN_ARG, collect_string(lexer), lexer));
		else if (lexer->c == '\'' || lexer->c == '"' || lexer->c == '|'
			|| lexer->c == '<' || lexer->c == '>' || lexer->c == '$')
			return (get_next_token2(lexer));
		if (lexer->flg_error)
			break ;
	}
	return (NULL);
}
