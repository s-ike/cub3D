/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:03:11 by sikeda            #+#    #+#             */
/*   Updated: 2020/12/04 00:16:08 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_ldigit(unsigned long num)
{
	int	digit;

	digit = 0;
	if (num == 0)
		return (1);
	while (0 < num)
	{
		num = num / 10;
		digit++;
	}
	return (digit);
}

char		*ft_ltoa(long n)
{
	char			*result;
	unsigned long	un;
	int				len;

	un = n < 0 ? -(n) : n;
	len = n < 0 ? cnt_ldigit(un) + 1 : cnt_ldigit(un);
	if (!(result = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[--len] = '0';
	else
	{
		while (0 < un)
		{
			result[--len] = un % 10 + '0';
			un /= 10;
		}
		if (n < 0 && 0 < len)
			result[--len] = '-';
	}
	return (result);
}
