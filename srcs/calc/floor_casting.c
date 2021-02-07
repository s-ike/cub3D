/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:58:09 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/07 22:58:10 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_casting(t_info *info)
{
	int	y;
	int	x;

	y = info->screen.h / 2 + 1;
	while (y < info->screen.h)
	{
		x = -1;
		while (++x < info->screen.w)
		{
			info->buf[y][x] = info->floor_color;
			info->buf[info->screen.h - y - 1][x] = info->ceilling_color;
		}
		y++;
	}
}
