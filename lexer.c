/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:33:34 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/12 22:43:04 by schoukou         ###   ########.fr       */
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
			return (init_token(TOKEN_CMD, collect_string(lexer)));
		}
		else if (lexer->c != '>' && lexer->c != '|'
			&& lexer->c != '<' && lexer->flg == 0)
			return (init_token(TOKEN_ARG, collect_string(lexer)));
		else if (lexer->c == '\'')
			return (handle_single_quote(lexer));
		else if (lexer->c == '"')
			return (handle_single_quote(lexer));
		else if (lexer->c == '|')
			return (collect_pipe(lexer));
		else if (lexer->c == '>')
		{
			lexer_advance(lexer);
			if (lexer->c == '>')
				return (lexer_advance_with_token(lexer, init_token(TOKEN_DRRD,
							get_current_char_as_string_redirection(lexer))));
			else
				return (lexer_advance_with_token(lexer, init_token(TOKEN_SRRD,
							get_current_char_as_string_redirection(lexer))));
		}
		else if (lexer->c == '<')
		{
			lexer_advance(lexer);
			if (lexer->c == '<')
				return (lexer_advance_with_token(lexer, init_token(TOKEN_HERDOC,
							get_current_char_as_string_redirection(lexer))));
			else
				return (lexer_advance_with_token(lexer, init_token(TOKEN_SLRD,
							get_current_char_as_string_redirection(lexer))));
		}
		else if (lexer->c == '$')
			return (init_token(TOKEN_ENV, get_current_char_as_string_2(lexer)));
		else
			return (lexer_advance_with_token(lexer, init_token(TOKEN_ARG,
						collect_string(lexer))));
	}
	return (NULL);
}
