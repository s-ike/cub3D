/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:39:34 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/19 16:13:34 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	set_speed(t_info *info)
{
	size_t	screen_size;
	double	square;

	if (__SIZE_MAX__ / info->screen.w < (size_t)info->screen.h)
		square = sqrt(__SIZE_MAX__);
	else
	{
		screen_size = (size_t)info->screen.w * (size_t)info->screen.h;
		square = sqrt(screen_size);
	}
	info->speed = square * MOVE_SPEED;
}

t_errmsg
	get_resolution(t_info *info, int *settings, char **split)
{
	t_screen	current;

	if (!split[1] || !split[2] || split[3] || *settings & (1 << SETTING_R))
		return (ERR_CUBFILE_R);
	if (!str_isdigit(split[1]) || !str_isdigit(split[2]))
		return (ERR_CUBFILE_R);
	info->screen.w = ft_atoi(split[1]);
	info->screen.h = ft_atoi(split[2]);
	if (info->screen.w <= 0 || info->screen.h <= 0)
		return (ERR_CUBFILE_R);
	mlx_get_screen_size(info->mlx, &current.w, &current.h);
	if (current.w < info->screen.w)
		info->screen.w = current.w;
	if (current.h < info->screen.h)
		info->screen.h = current.h;
	*settings |= (1 << SETTING_R);
	set_speed(info);
	return (NULL);
}
