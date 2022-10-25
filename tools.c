/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:10:53 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/24 01:35:20 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	int		i;
	char	**copy;
	int		x;

	i = 0;
	x = count_2d(env);
	copy = malloc(sizeof(char *) * (x + 1));
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	*search_in_env(char *c, t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->env[i])
	{
		if (!ft_strncmp(lexer->env[i], c, ft_strlen(c)))
		{
			free(c);
			return (ft_substr(lexer->env[i], ft_strlen(c),
					ft_strlen(lexer->env[i]) - ft_strlen(c)));
		}
		i++;
	}
	return (NULL);
}

char	*dollar_handler2(t_lexer *lexer, char *s, char *c)
{
	while (lexer->c)
	{
		if (lexer->c != '_' && !ft_isalnum(lexer->c))
			break ;
		else
		{
			c = get_current_char_as_string(lexer);
			s = ft_strjoin(s, c);
			free(c);
			lexer_advance(lexer);
		}
	}
	s = ft_strjoin(s, "=");
	s = search_in_env(s, lexer);
	if (s == NULL)
		s = ft_strdup("");
	return (s);
}

char	*dollar_handler(t_lexer *lexer)
{
	char	*s;
	char	*c;

	exitm = 0;
	s = ft_strdup("");
	c = ft_strdup("");
	if (lexer->c == '$')
		lexer_advance(lexer);
	if (lexer->c == '?')
	{
		s = ft_strjoin(s, ft_itoa(exitm));
		free(c);
		lexer_advance(lexer);
		return (s);
	}
	if (lexer->c != '_' && !ft_isalnum(lexer->c))
	{
		s = ft_strjoin(s, "$");
		free(c);
		return (s);
	}
	s = dollar_handler2(lexer, s, c);
	return (s);
}
