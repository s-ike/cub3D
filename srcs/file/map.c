/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:20:11 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 01:20:30 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_map_size_too_large(size_t len, int line_num)
{
	if (COL < len || ROW < line_num)
		return (TRUE);
	return (FALSE);
}

static t_bool	is_map_with_only_correct_chr(t_info *info, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strchr(" 012NSEW", line[i]))
		{
			if (ft_strchr("NSEW", line[i]))
			{
				if (info->pos_x == 0.0 && info->pos_y == 0.0)
				{
					info->pos_x = (double)info->map_line_num + 0.49;
					info->pos_y = i + 0.49;
					info->map_start_dir = line[i];
				}
				else
					return (FALSE);
			}
		}
		else
			return (FALSE);
	return (TRUE);
}

t_errmsg		get_map(t_info *info, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (is_map_size_too_large(len, info->map_line_num + 1) == TRUE)
		return (ERR_BIG_MAP);
	if (is_map_with_only_correct_chr(info, line) == FALSE)
		return (ERR_CHR_MAP);
	ft_strlcpy(info->map[info->map_line_num], line, len + 1);
	info->map_line_num++;
	return (NULL);
}
