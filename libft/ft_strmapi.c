/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:14:31 by afaris            #+#    #+#             */
/*   Updated: 2021/11/14 16:42:40 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;
	char			*old;

	if (!s || !f)
		return (0);
	old = (char *)s;
	new = (char *)malloc(ft_strlen(old) + 1);
	i = 0;
	if (!new)
		return (0);
	while (s[i])
	{
		new[i] = f(i, old[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
