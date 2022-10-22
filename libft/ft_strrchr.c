/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:27:58 by afaris            #+#    #+#             */
/*   Updated: 2021/11/20 12:57:29 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	ch;
	char			*str;

	str = (char *)s;
	ch = c;
	len = ft_strlen(s);
	if (!s)
		return (NULL);
	while (len)
	{
		if (s[len] == ch)
			return (&str[len]);
		len--;
	}
	if (s[len] == ch)
		return (&str[len]);
	return (0);
}
