/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:05:22 by afaris            #+#    #+#             */
/*   Updated: 2021/11/14 18:40:37 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_matching(char *str, char *sub, size_t len)
{
	size_t	i;
	
	i = 0;
	while (str[i] && str[i] == sub[i] && i < len)
	{
		i++;
	}
	if (i == ft_strlen(sub))
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*sub;
	size_t	i;

	i = 0;
	str = (char *)haystack;
	sub = (char *)needle;
	if (!sub[i])
		return (str);
	while (str[i] && i < len)
	{
		if (i + ft_strlen(sub) > len)
			return (0);
		else if (str[i] == sub[0] && is_matching(&str[i], sub, len))
			return (&str[i]);
		i++;
	}
	return (0);
}
