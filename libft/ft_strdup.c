/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:52:58 by afaris            #+#    #+#             */
/*   Updated: 2022/10/26 04:54:52 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cp;
	int		i;

	i = 0;
	cp = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!cp)
		return (NULL);
	if (!s1)
	{
		free(cp);
		return (NULL);
	}
	while (s1[i])
	{
		cp[i] = s1[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
