/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:59:22 by afaris            #+#    #+#             */
/*   Updated: 2021/11/14 18:41:07 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_there(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	end_pos(char const *s1, char const *set, int start_pos)
{
	int		i;

	i = ft_strlen(s1) - 1;
	while (i >= start_pos)
	{
		if (!is_there(s1[i], set))
			return (i);
		else if (is_there(s1[i], set) && (!is_there(s1[i - 1], set)))
			return (i - 1);
		i--;
	}
	return (ft_strlen(s1));
}

static size_t	start_pos(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (s1[i])
	{
		if (!is_there(s1[i], set))
			return (i);
		else if (is_there(s1[i], set) && !is_there(s1[i + 1], set))
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (0);
	start = start_pos(s1, set);
	end = end_pos(s1, set, start);
	str = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (!str)
		return (0);
	while (start <= end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
