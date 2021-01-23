/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:57:51 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/08 17:02:19 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dst_len)
		return (src_len + dstsize);
	dst += dst_len;
	dstsize -= dst_len;
	while (*src && 0 < (dstsize-- - 1))
		*dst++ = *src++;
	*dst = '\0';
	return (dst_len + src_len);
}
