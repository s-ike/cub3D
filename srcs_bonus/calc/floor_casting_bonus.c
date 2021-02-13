/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:58:09 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/14 01:20:33 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_floor_calc(t_info *info, t_floorcalc *calc, int y)
{
	int		p;
	float	pos_z;
	float	row_distance;

	calc->ray_dir_x0 = info->dir_x - info->plane_x;
	calc->ray_dir_y0 = info->dir_y - info->plane_y;
	calc->ray_dir_x1 = info->dir_x + info->plane_x;
	calc->ray_dir_y1 = info->dir_y + info->plane_y;
	p = y - info->screen.h / 2;
	pos_z = 0.5 * info->screen.h;
	row_distance = pos_z / p;
	calc->floor_step_x = row_distance * (calc->ray_dir_x1 - calc->ray_dir_x0)
		/ info->screen.w;
	calc->floor_step_y = row_distance * (calc->ray_dir_y1 - calc->ray_dir_y0)
		/ info->screen.w;
	calc->floor_x = info->pos_x + row_distance * calc->ray_dir_x0;
	calc->floor_y = info->pos_y + row_distance * calc->ray_dir_y0;
}

static void	set_floor_color(t_info *info, t_floorcalc *calc, int y, int x)
{
	int	cell_x;
	int	cell_y;
	int tx;
	int ty;
	int color;

	cell_x = (int)calc->floor_x;
	cell_y = (int)calc->floor_y;
	tx = (int)(info->texture[TEX_FLOOR].w * (calc->floor_x - cell_x))
		& (info->texture[TEX_FLOOR].w - 1);
	ty = (int)(info->texture[TEX_FLOOR].h * (calc->floor_y - cell_y))
		& (info->texture[TEX_FLOOR].h - 1);
	color = info->texture[TEX_FLOOR].data[info->texture[TEX_FLOOR].w * ty + tx];
	info->buf[y][x] = color;
}

static void	set_ceilling_color(t_info *info, t_floorcalc *calc, int y, int x)
{
	int	cell_x;
	int	cell_y;
	int tx;
	int ty;
	int color;

	cell_x = (int)calc->floor_x;
	cell_y = (int)calc->floor_y;
	tx = (int)(info->texture[TEX_CEILLING].w * (calc->floor_x - cell_x))
		& (info->texture[TEX_FLOOR].w - 1);
	ty = (int)(info->texture[TEX_CEILLING].h * (calc->floor_y - cell_y))
		& (info->texture[TEX_FLOOR].h - 1);
	color = info->texture[TEX_CEILLING].data[
		info->texture[TEX_CEILLING].w * ty + tx];
	info->buf[info->screen.h - y - 1][x] = color;
}

void		floor_casting(t_info *info)
{
	t_floorcalc	calc;
	int			y;
	int			x;

	y = info->screen.h / 2 + 1;
	while (y < info->screen.h)
	{
		init_floor_calc(info, &calc, y);
		x = -1;
		while (++x < info->screen.w)
		{
			set_floor_color(info, &calc, y, x);
			set_ceilling_color(info, &calc, y, x);
			calc.floor_x += calc.floor_step_x;
			calc.floor_y += calc.floor_step_y;
		}
		y++;
	}
}
