/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:39:34 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/20 23:09:32 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	is_invalid_format(char **split)
{
	return (
		!split[1] || !split[2] || split[3]
		|| !str_isdigit(split[1])
		|| !str_isdigit(split[2])
		|| ft_atoi(split[1]) <= 0
		|| ft_atoi(split[2]) <= 0
		|| split[1][0] == '0'
		|| split[2][0] == '0');
}

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

	if (*settings & (1 << SETTING_R))
		return (ERR_CUBFILE_R);
	if (is_invalid_format(split))
		return (ERR_CUBFILE_R);
	info->screen.w = ft_atoi(split[1]);
	info->screen.h = ft_atoi(split[2]);
	if (info->mode == GAMEMODE)
	{
		mlx_get_screen_size(info->mlx, &current.w, &current.h);
		if (current.w < info->screen.w)
			info->screen.w = current.w;
		if (current.h < info->screen.h)
			info->screen.h = current.h;
	}
	*settings |= (1 << SETTING_R);
	set_speed(info);
	return (NULL);
}
