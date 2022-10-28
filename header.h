/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:23:14 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/28 13:01:40 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include "token.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>

int g_exitm;

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
	int				flg;
	int				x;
	int				y;
	int				flg_error;
	char			**env;
}	t_lexer;

typedef struct s_rdr
{
	int				type;
	char			*value;
	struct s_rdr	*next;
	int				herdoc;
	int				fd;
}	t_rdr;

typedef struct s_env
{
    char            *key;
    char            *value;
    int             is_printed;
    struct s_env    *next;
} t_env;

typedef struct s_parse
{
	int				id;
	char			*cmd;
	char			**arg;
	t_rdr			*rdr;
    t_env   		*env;
	int				pid;
	char			*path;
	char			**cmd_2d;
	char			**env_2d;
	int				read_src;
	int				exit_code;
	int				write_dst;
	struct s_parse	*next;
}	t_parse;

t_lexer	*init_lexer(char *contents, t_lexer *lexer);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_space(t_lexer *lexer);
// t_token	*init_tok÷en(int type, char *value);
t_token	*init_token(int type, char *value, t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
char	*collect_string(t_lexer *lexer);
char	*get_current_char_as_string(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_lexer	*skip_single_quote(t_lexer *lexer, int sq);
t_token	*handle_single_quote(t_lexer *lexer);
int		check_single_quote(t_lexer *lexer);
char	*get_current_char_as_string_2(t_lexer *lexer);
t_token	*handle_double_quote(t_lexer *lexer);
char	*get_current_char_as_string_3(t_lexer *lexer);
int		redirect_check(t_lexer *lexer);
char	*get_current_char_as_string_redirection(t_lexer *lexer);
void	lexer_back(t_lexer *lexer);
char	*collect_string_2(t_lexer *lexer, char *join);
int		check_if_next_quote(t_lexer *lexer);
t_token	*collect_pipe(t_lexer *lexer);
char	**copy_env(char **env);
char	*dollar_handler(t_lexer *lexer);
t_parse	*init_parsing(t_token **token, t_lexer *lexer);
void	error_rdr(t_lexer *lexer);
char	*stock_rdr_value(t_lexer *lexer, char *str);
char	*collect_string_handle(t_lexer *lexer, char *s);
char	*join_to_str(t_lexer *lexer);
t_rdr	*add_rdr(char *str, int type, int herdoc);
void	add_back_parse(t_parse **parse, t_parse *tmp);
void	add_back_rdr(t_rdr **rdr, t_rdr *tmp);
int	count_arg(t_token *head);
#endif
