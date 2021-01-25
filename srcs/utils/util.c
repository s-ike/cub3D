/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 02:21:49 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/25 11:31:22 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	safe_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int		str_isdigit(const char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}
