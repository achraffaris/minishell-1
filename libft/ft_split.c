/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:07:14 by afaris            #+#    #+#             */
/*   Updated: 2021/11/24 18:29:44 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_deallocate(int i, char **arr)
{
	while (i)
	{
		free(arr[i]);
		i--;
	}
	free (arr);
	return (0);
}

static int	fill_arr(int pos, char *arr, const char *str, char c)
{
	int	i;

	i = 0;
	while (str[pos] && str[pos] == c)
	{
		pos++;
	}
	while (str[pos] && str[pos] != c)
	{
		arr[i] = str[pos];
		i++;
		pos++;
	}
	while (str[pos] && str[pos] == c)
	{
		pos++;
	}
	arr[i] = '\0';
	return (pos);
}

static int	word_count(const char *str, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (str[i] && str[i] != c)
		k++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			k++;
		i++;
	}
	return (k);
}

static char	*alocate_arr(const char *str, char c)
{
	int		i;
	char	*new;
	int		j;

	j = 0;
	i = 0;
	while (str[j] && str[j] == c)
	{
		j++;
	}
	while (str[j] && str[j] != c)
	{
		i++;
		j++;
	}
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		cw;
	int		i;
	int		pos;

	pos = 0;
	i = 0;
	if (!s)
		return (0);
	cw = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (cw + 1));
	if (!arr)
		return (NULL);
	while (i < cw)
	{
		arr[i] = alocate_arr(&s[pos], c);
		if (! arr[i])
			return (ft_deallocate(i, arr));
		pos = fill_arr(pos, arr[i], s, c);
		i++;
	}
	arr[cw] = 0;
	return (arr);
}
