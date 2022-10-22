/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:44:46 by afaris            #+#    #+#             */
/*   Updated: 2021/11/23 17:24:37 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*de;
	unsigned char	*sr;

	if (dest == src)
		return (dest);
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	de = ((unsigned char *)dest);
	sr = ((unsigned char *)src);
	while (n)
	{
		de[n - 1] = sr[n - 1];
		n--;
	}
	return (dest);
}
