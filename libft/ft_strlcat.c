/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:02:30 by afaris            #+#    #+#             */
/*   Updated: 2021/11/21 19:51:32 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;
	size_t	len;
	size_t	i_dst_len;

	i = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	i_dst_len = dst_len;
	if (dstsize <= i_dst_len)
		return (dstsize + ft_strlen(src));
	len = dstsize - dst_len - 1;
	while (len && src[i])
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
		len--;
	}
	dst[dst_len] = '\0';
	return (i_dst_len + ft_strlen(src));
}
