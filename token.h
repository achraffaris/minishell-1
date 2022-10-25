/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:29:16 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/22 23:37:25 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum
	{
		TOKEN_CMD,
		TOKEN_ARG,
		TOKEN_PIPE,
		TOKEN_HERDOC,
		TOKEN_SLRD,
		TOKEN_SRRD,
		TOKEN_DRRD,
		TOKEN_ERROR,
		TOKEN_ENV,
	}	e_type;
	int				flag_cmg;
	struct s_token	*next;
	char			*value;
	int				rdr_flg;
}	t_token;

#endif
