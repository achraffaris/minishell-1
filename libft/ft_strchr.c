/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:29:12 by afaris            #+#    #+#             */
/*   Updated: 2021/11/19 20:19:54 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	ch;

	ch = c;
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (&str[i]);
		i++;
	}
	if (str[i] == ch)
		return (&str[i]);
	return (NULL);
}
