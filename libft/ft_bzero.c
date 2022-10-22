/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:18:31 by afaris            #+#    #+#             */
/*   Updated: 2021/11/24 11:21:51 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		str[i] = '\0';
		i++;
	}
}
