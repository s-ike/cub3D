/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:26:34 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 01:57:39 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_errmsg	validate_filename(char *filename, char *type)
{
	char	*extension;

	if (!ft_strcmp(filename, type))
		return (ERR_CUBFILE_EXT);
	if ((extension = ft_strrchr(filename, '.')))
	{
		if (!ft_strcmp(extension, type))
			return (NULL);
	}
	return (ERR_CUBFILE_EXT);
}

t_errmsg	validate_readable_file(char *filename, int *fd)
{
	char	buf;

	if ((*fd = open(filename, O_RDONLY)) < 0)
		return (strerror(errno));
	if (read(*fd, &buf, 0) < 0)
		return (strerror(errno));
	return (NULL);
}

void		clear_split(char ***split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while ((*split)[i])
		i++;
	if (i == 0)
		return ;
	while (0 <= --i)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
}

int			is_uint8_range(int n)
{
	return (0 <= n && n <= EIGHT_BIT_MAX);
}
