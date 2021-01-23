/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:08:54 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/20 00:03:27 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\r'
			|| c == '\f' || c == '\t' || c == '\v');
}

static int	is_over_long(unsigned long n, int is_max)
{
	unsigned long	limit;

	limit = __LONG_MAX__;
	if (!is_max)
		limit++;
	return ((limit < n));
}

static int	is_over_max_long(unsigned long n)
{
	return (is_over_long(n, 1));
}

static int	is_over_min_long(unsigned long n)
{
	return (is_over_long(n, 0));
}

long		ft_atol(const char *str)
{
	unsigned long	num;
	int				sign;

	num = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = *str == '-' ? -1 : 1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		num = (num * 10) + (*str++ - '0');
		if (0 < sign && is_over_max_long(num))
			return (__LONG_MAX__);
		if (sign < 0 && is_over_min_long(num))
			return (-__LONG_MAX__ - 1);
	}
	return (num * sign);
}
