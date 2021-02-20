/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_sub_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:49:24 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/20 11:38:39 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_tex_calc2(t_info *info, t_wallcalc *wallcalc,
								t_walltex *walltex, int side)
{
	walltex->wall_x -= floor(walltex->wall_x);
	walltex->tex_x =
		(int)(walltex->wall_x * (double)info->texture[walltex->tex_num].w);
	if (side == 0 && wallcalc->ray_dir.x > 0)
		walltex->tex_x = info->texture[walltex->tex_num].w - walltex->tex_x - 1;
	if (side == 1 && wallcalc->ray_dir.y < 0)
		walltex->tex_x = info->texture[walltex->tex_num].w - walltex->tex_x - 1;
	walltex->tex_step =
		1.0 * info->texture[walltex->tex_num].h / walltex->line_height;
	walltex->tex_pos =
		(walltex->draw_start - info->screen.h / 2 + walltex->line_height / 2)
			* walltex->tex_step;
}

static void	init_tex_calc1(t_info *info, t_wallcalc *wallcalc,
							t_walltex *walltex, int side)
{
	walltex->line_height = (int)(info->screen.h / wallcalc->wall_dist);
	walltex->draw_start = -walltex->line_height / 2 + info->screen.h / 2;
	if (walltex->draw_start < 0)
		walltex->draw_start = 0;
	walltex->draw_end = walltex->line_height / 2 + info->screen.h / 2;
	if (walltex->draw_end >= info->screen.h)
		walltex->draw_end = info->screen.h;
	if (side)
		walltex->tex_num = wallcalc->ray_dir.y < 0 ? TEX_EAST : TEX_WEST;
	else
		walltex->tex_num = wallcalc->ray_dir.x < 0 ? TEX_SOUTH : TEX_NORTH;
	if (side == 0)
		walltex->wall_x =
			info->pos_y + wallcalc->wall_dist * wallcalc->ray_dir.y;
	else
		walltex->wall_x =
			info->pos_x + wallcalc->wall_dist * wallcalc->ray_dir.x;
}

void		draw_stripe(t_info *info, t_wallcalc *wallcalc, int side, int x)
{
	t_walltex	walltex;
	int			tex_y;
	int			color;
	int			y;

	init_tex_calc1(info, wallcalc, &walltex, side);
	init_tex_calc2(info, wallcalc, &walltex, side);
	y = walltex.draw_start;
	while (y < walltex.draw_end)
	{
		tex_y = (int)fmin((int)walltex.tex_pos,
					(info->texture[walltex.tex_num].h - 1));
		walltex.tex_pos += walltex.tex_step;
		color =
			info->texture[walltex.tex_num].data[info->texture[walltex.tex_num].h
				* tex_y + walltex.tex_x];
		info->buf[y][x] = color;
		y++;
	}
}
