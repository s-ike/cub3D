/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:53:00 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/08 17:02:19 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (!s)
		return (NULL);
	if ((s_len = ft_strlen(s)) <= start || !len)
		return ((char *)ft_calloc(1, sizeof(char)));
	len = (s_len < len) ? (s_len - start) : len;
	if (!(sub = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	s += start;
	ft_strlcpy(sub, s, len + 1);
	return (sub);
}
