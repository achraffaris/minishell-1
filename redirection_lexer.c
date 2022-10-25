/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:54:29 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/23 21:55:59 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*stock_rdr_value(t_lexer *lexer, char *str)
{
	if (lexer->c == '$')
		str = ft_strjoin(str, dollar_handler(lexer));
	else if (lexer->c == '\'' || lexer->c == '"')
	{
		str = ft_strjoin(str, join_to_str(lexer));
		lexer_advance(lexer);
	}
	else
		str = ft_strjoin(str, get_current_char_as_string(lexer));
	if (lexer->c != '\0' && lexer->c != '\'' && lexer->c != '"'
		&& lexer->c != '>' && lexer->c != '<'
		&& lexer->c != ' ' && lexer->c != '|' && lexer->c != '$')
		lexer_advance(lexer);
	return (str);
}

char	*get_current_char_as_string_redirection(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	if (lexer->c == '>' || lexer->c == '<')
		lexer_advance(lexer);
	if (lexer->c == ' ')
		lexer_skip_space(lexer);
	if (lexer->c == '>' || lexer->c == '<'
		|| lexer->c == '\0' || lexer->c == '|')
		lexer->flg_error = 1;
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c)
	{
		if (lexer->c == ' ' || lexer->c == '|'
			|| lexer->c == '<' || lexer->c == '>')
			break ;
		str = stock_rdr_value(lexer, str);
	}
	return (str);
}

int	redirect_check(t_lexer *lexer)
{
	if (lexer->c == 60 || lexer->c == 62)
		return (0);
	return (1);
}

t_token	*collect_pipe(t_lexer *lexer)
{
	lexer->flg = 1;
	return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
				get_current_char_as_string(lexer), lexer)));
}
