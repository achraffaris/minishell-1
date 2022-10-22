/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:57:04 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/16 23:38:10 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	}
	if (lexer->c != '\'' && lexer->c != '"')
		lexer->flg_error = 1;
	return (str);
}

t_token	*handle_single_quote(t_lexer *lexer)
{
	char	*str;
	char	*str2;
	char	*s;

	str = ft_strdup("");
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == '|'
			|| lexer->c == '<' || lexer->c == '>')
			break ;
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
	}
	if (lexer->flg == 1)
	{
		lexer->flg = 0;
		return (init_token(TOKEN_CMD, str));
	}
	else
		return (init_token(TOKEN_ARG, str));
}

t_token	*handle_double_quote(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	str[0] = '\0';
	lexer_advance(lexer);
	while (lexer->c != '\"')
	{
		str = ft_strjoin(str, get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	if (lexer->flg == 1)
		return (init_token(TOKEN_CMD, str));
	else
		return (init_token(TOKEN_ARG, str));
}

char	*collect_string(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\0')
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

char	*get_current_char_as_string_redirection(t_lexer *lexer)
{
	char	*str;
	int		size;

	size = 0;
	str = malloc(size + 1);
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
	}
	return (str);
}

int	redirect_check(t_lexer *lexer)
{
	if (lexer->c == 60 || lexer->	c == 62)
		return (0);
	return (1);
}

t_token	*collect_pipe(t_lexer *lexer)
{
	lexer->flg = 1;
	return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
				get_current_char_as_string(lexer))));
}
