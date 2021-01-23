/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 00:13:49 by sikeda            #+#    #+#             */
/*   Updated: 2020/12/04 00:14:02 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_lldigit(unsigned long long num, unsigned int base)
{
	int	digit;

	digit = 0;
	if (num == 0)
		return (1);
	while (0 < num)
	{
		num /= base;
		digit++;
	}
	return (digit);
}

char		*ft_ulltoa_base(
				unsigned long long n, unsigned int base, int is_upper)
{
	char	*result;
	int		len;
	char	base_char;

	if (base < 2 || 36 < base)
		return (NULL);
	len = cnt_lldigit(n, base);
	if (!(result = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[--len] = '0';
	while (0 < n)
	{
		if (n % base < 10)
			base_char = '0';
		else
			base_char = is_upper ? 'A' - 10 : 'a' - 10;
		result[--len] = n % base + base_char;
		n /= base;
	}
	return (result);
}
