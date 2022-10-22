/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:52:02 by afaris            #+#    #+#             */
/*   Updated: 2021/11/21 19:58:13 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*str;
	unsigned char	ch;

	ch = c;
	str = (unsigned char *)s;
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			if (!str[i] && str[i] == ch)
				return (&str[i]);
			if (str[i] == ch)
				return (&str[i]);
			i++;
		}
	}
	return (NULL);
}
