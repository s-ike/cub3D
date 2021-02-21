/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 02:21:49 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:17:39 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void
	safe_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int
	str_isdigit(const char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int
	chrcount(const char *s, char c)
{
	int				ret;
	unsigned char	uc;

	ret = 0;
	uc = (unsigned)c;
	while (*s)
		if (*s++ == uc)
			ret++;
	return (ret);
}

void
	set_vals_for_2intvars(int *v1, int *v2, int n1, int n2)
{
	if (v1)
		*v1 = n1;
	if (v2)
		*v2 = n2;
}
