/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:48:59 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/23 21:54:04 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*collect_string(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\0')
	{
		if (lexer->c == '"' || lexer->c == '\'')
			s = collect_string_handle(lexer, s);
		else if (lexer->c == '$')
			s = collect_string_handle(lexer, s);
		else if (lexer->c != '\'' && lexer->c != '"' && lexer->c != '>'
			&& lexer->c != '<' && lexer->c != ' '
			&& lexer->c != '|' && lexer->c != '\0')
		{
			s = get_current_char_as_string(lexer);
			lexer_advance(lexer);
		}
		else
			break ;
		value = ft_strjoin(value, s);
		free(s);
	}
	return (value);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	if (token->e_type == TOKEN_PIPE)
		lexer_advance(lexer);
	(void)lexer;
	return (token);
}

char	*get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = malloc(2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*get_current_char_as_string_2(t_lexer *lexer)
{
	char	*str;
	int		size;

	size = 0;
	str = malloc(size + 1);
	while (lexer->c != ' ' && lexer->c != '\0')
	{
		str = ft_strjoin(str, get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (str);
}

char	*get_current_char_as_string_3(t_lexer *lexer)
{
	char	*str;
	int		size;

	size = 0;
	str = malloc(size + 1);
	while (lexer->c != '\0' && (redirect_check(lexer)))
	{
		str = ft_strjoin(str, get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (str);
}
