/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:57:04 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/23 21:49:27 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*join_to_str_handle(t_lexer *lexer, char *s, char *str)
{
	lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != '"')
	{
		if (lexer->c == '$')
			s = dollar_handler(lexer);
		else
		{
			s = get_current_char_as_string(lexer);
			if (lexer->c != '\0' && lexer->c != '"')
				lexer_advance(lexer);
		}
		str = ft_strjoin(str, s);
		free(s);
	}
	return (str);
}

char	*join_to_str(t_lexer *lexer)
{
	char	*str;
	char	*s;

	str = ft_strdup("");
	if (lexer->c == '\'')
	{
		lexer_advance(lexer);
		while (lexer->c != 0 && lexer->c != '\'')
		{
			s = get_current_char_as_string(lexer);
			str = ft_strjoin(str, s);
			free(s);
			if (lexer->c != '\0' && lexer->c != '\'')
				lexer_advance(lexer);
		}
	}
	if (lexer->c == '"')
		str = join_to_str_handle(lexer, s, str);
	if (lexer->c != '\'' && lexer->c != '"')
		lexer->flg_error = 1;
	return (str);
}

char	*stock_value(t_lexer *lexer, char *str)
{
	char	*s;
	char	*str2;

	if (lexer->c == '"' || lexer->c == '\'')
	{
		str2 = join_to_str(lexer);
		str = ft_strjoin(str, str2);
		lexer_advance(lexer);
	}
	else if (lexer->c != '"' && lexer->c != '\'')
	{
		s = get_current_char_as_string(lexer);
		str = ft_strjoin(str, s);
		free (s);
		lexer_advance(lexer);
	}
	return (str);
}

t_token	*handle_single_quote(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == '|'
			|| lexer->c == '<' || lexer->c == '>')
			break ;
		str = stock_value(lexer, str);
	}
	if (lexer->flg == 1)
	{
		lexer->flg = 0;
		return (init_token(TOKEN_CMD, str, lexer));
	}
	else
		return (init_token(TOKEN_ARG, str, lexer));
}

char	*collect_string_handle(t_lexer *lexer, char *s)
{
	if (lexer->c == '"' || lexer->c == '\'')
	{
		s = join_to_str(lexer);
		lexer_advance(lexer);
	}
	else if (lexer->c == '$')
	{
		lexer_advance(lexer);
		if (lexer->c != '\'' && lexer->c != '"')
			s = dollar_handler(lexer);
		else
			s = ft_strdup("");
	}
	return (s);
}
