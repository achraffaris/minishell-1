/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:27:33 by afaris            #+#    #+#             */
/*   Updated: 2021/11/16 17:27:56 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_count(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*convert(int n, int len, char *str)
{
	unsigned int	nb;
	int				i;

	i = 0;
	if (n < 0)
	{
		nb = -n;
		str[i] = '-';
		i++;
	}
	else
		nb = n;
	while (len >= i && nb)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = len_count(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	if (n == 0)
	{
		str[len] = '0';
		return (str);
	}
	return (convert(n, len, str));
}
