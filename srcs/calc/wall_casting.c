/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 00:46:19 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/10 10:33:03 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_calc(t_info *info, t_wallcalc *wallcalc, int x)
{
	wallcalc->camera_x = 2 * x / (double)info->screen.w - 1;
	wallcalc->ray_dir.x = info->dir_x + info->plane_x * wallcalc->camera_x;
	wallcalc->ray_dir.y = info->dir_y + info->plane_y * wallcalc->camera_x;
	wallcalc->map_x = (int)info->pos_x;
	wallcalc->map_y = (int)info->pos_y;
	wallcalc->side_dist.x = 0;
	wallcalc->side_dist.y = 0;
	wallcalc->delta_dist.x = fabs(1 / wallcalc->ray_dir.x);
	wallcalc->delta_dist.y = fabs(1 / wallcalc->ray_dir.y);
	wallcalc->wall_dist = 0.0;
}

static void	get_step(t_info *info, t_wallcalc *wallcalc, t_step *step)
{
	if (wallcalc->ray_dir.x < 0)
	{
		step->x = -1;
		wallcalc->side_dist.x =
			(info->pos_x - wallcalc->map_x) * wallcalc->delta_dist.x;
	}
	else
	{
		step->x = 1;
		wallcalc->side_dist.x =
			(wallcalc->map_x + 1.0 - info->pos_x) * wallcalc->delta_dist.x;
	}
	if (wallcalc->ray_dir.y < 0)
	{
		step->y = -1;
		wallcalc->side_dist.y =
			(info->pos_y - wallcalc->map_y) * wallcalc->delta_dist.y;
	}
	else
	{
		step->y = 1;
		wallcalc->side_dist.y =
			(wallcalc->map_y + 1.0 - info->pos_y) * wallcalc->delta_dist.y;
	}
}

static void	add_sprite(t_info *info, t_wallcalc *wallcalc)
{
	t_splist	*new;

	info->spmap[wallcalc->map_x][wallcalc->map_y] = 1;
	if (!(new = splst_new(wallcalc->map_x, wallcalc->map_y)))
		exitgame_with_errmsg(ERR_CUB, info);
	splist_add_front(&info->splist, new);
}

static int	dda(t_info *info, t_wallcalc *wallcalc, t_step *step)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (wallcalc->side_dist.x < wallcalc->side_dist.y)
		{
			wallcalc->side_dist.x += wallcalc->delta_dist.x;
			wallcalc->map_x += step->x;
			side = 0;
		}
		else
		{
			wallcalc->side_dist.y += wallcalc->delta_dist.y;
			wallcalc->map_y += step->y;
			side = 1;
		}
		if (info->map[wallcalc->map_x][wallcalc->map_y] == CHECKED_SPRITE
		&& !info->spmap[wallcalc->map_x][wallcalc->map_y])
			add_sprite(info, wallcalc);
		if (info->map[wallcalc->map_x][wallcalc->map_y] == CHECKED_WALL)
			hit = 1;
	}
	return (side);
}

static void	init_tex_calc(t_info *info, t_wallcalc *wallcalc, t_walltex *w_tex, int side)
{
	w_tex->line_height = (int)(info->screen.h / wallcalc->wall_dist);
	w_tex->draw_start = -w_tex->line_height / 2 + info->screen.h / 2;
	if (w_tex->draw_start < 0)
		w_tex->draw_start = 0;
	w_tex->draw_end = w_tex->line_height / 2 + info->screen.h / 2;
	if (w_tex->draw_end >= info->screen.h)
		w_tex->draw_end = info->screen.h - 1;
	if (side)
		w_tex->tex_num = wallcalc->ray_dir.y < 0 ? TEX_WEST : TEX_EAST;
	else
		w_tex->tex_num = wallcalc->ray_dir.x < 0 ? TEX_NORTH : TEX_SOUTH;
	if (side == 0)
		w_tex->wall_x = info->pos_y + wallcalc->wall_dist * wallcalc->ray_dir.y;
	else
		w_tex->wall_x = info->pos_x + wallcalc->wall_dist * wallcalc->ray_dir.x;
	w_tex->wall_x -= floor(w_tex->wall_x);
	w_tex->tex_x = (int)(w_tex->wall_x * (double)info->texture[w_tex->tex_num].w);
	if (side == 0 && wallcalc->ray_dir.x > 0)
		w_tex->tex_x = info->texture[w_tex->tex_num].w - w_tex->tex_x - 1;
	if (side == 1 && wallcalc->ray_dir.y < 0)
		w_tex->tex_x = info->texture[w_tex->tex_num].w - w_tex->tex_x - 1;
	w_tex->tex_step = 1.0 * info->texture[w_tex->tex_num].h / w_tex->line_height;
	w_tex->tex_pos = (w_tex->draw_start - info->screen.h / 2 + w_tex->line_height / 2) * w_tex->tex_step;
}

static void	draw_stripe(t_info *info, t_wallcalc *wallcalc, int side, int x)
{
	t_walltex	walltex;
	int			tex_y;
	int			color;
	int			y;

	init_tex_calc(info, wallcalc, &walltex, side);
	y = walltex.draw_start;
	while (y < walltex.draw_end)
	{
		tex_y = (int)fmin((int)walltex.tex_pos,
					(info->texture[walltex.tex_num].h - 1));
		walltex.tex_pos += walltex.tex_step;
		color = info->texture[walltex.tex_num].data[info->texture[walltex.tex_num].h * tex_y + walltex.tex_x];
		info->buf[y][x] = color;
		y++;
	}
}

void		wall_casting(t_info *info)
{
	t_wallcalc	wallcalc;
	int			side;
	t_step		step;
	int			x;

	x = 0;
	while (x < info->screen.w)
	{
		init_calc(info, &wallcalc, x);
		get_step(info, &wallcalc, &step);
		side = dda(info, &wallcalc, &step);
		if (side == 0)
			wallcalc.wall_dist =
				(wallcalc.map_x - info->pos_x + (1 - step.x) / 2) /
					wallcalc.ray_dir.x;
		else
			wallcalc.wall_dist =
				(wallcalc.map_y - info->pos_y + (1 - step.y) / 2) /
					wallcalc.ray_dir.y;
		draw_stripe(info, &wallcalc, side, x);
		info->z_buffer[x] = wallcalc.wall_dist;
		x++;
	}
}
