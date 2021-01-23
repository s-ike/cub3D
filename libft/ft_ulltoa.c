/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 00:13:06 by sikeda            #+#    #+#             */
/*   Updated: 2020/12/04 00:13:07 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_lldigit(unsigned long long num)
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

char		*ft_ulltoa(unsigned long long n)
{
	char	*result;
	int		len;

	len = cnt_lldigit(n);
	if (!(result = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[--len] = '0';
	while (0 < n)
	{
		result[--len] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
