/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 23:24:01 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/08 17:02:19 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	len;

	len = ft_strlen(s1);
	if (!(cpy = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	return (ft_memcpy(cpy, s1, len + 1));
}
