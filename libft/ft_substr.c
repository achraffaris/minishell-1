/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:26:34 by afaris            #+#    #+#             */
/*   Updated: 2021/11/21 20:18:45 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (0);
	while (s[start] && i < len && start < ft_strlen(s))
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
