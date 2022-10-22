/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:56:06 by afaris            #+#    #+#             */
/*   Updated: 2021/11/23 18:33:18 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int				i;
	unsigned char	*de;
	unsigned char	*sr;

	i = 0;
	de = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (!de && !sr)
		return (0);
	while (n--)
	{
		de[i] = sr[i];
		i++;
	}
	return (de);
}
