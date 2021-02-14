/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:57:31 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/14 16:29:52 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_info *info, int tex_x, int tex_y)
{
	return (info->texture[TEX_SPRITE].data[
				info->texture[TEX_SPRITE].w * tex_y + tex_x]);
}

static void	draw_sprite_stripe_imple(t_info *info, t_spcalc *spcalc,
										int tex_x, int stripe)
{
	int	color;
	int	tex_y;
	int	y;
	int	d;
	int	size_l;

	size_l = info->texture[TEX_SPRITE].size_l;
	y = spcalc->draw_start_y;
	while (y < spcalc->draw_end_y)
	{
		d = y * size_l - info->screen.h * (size_l / 2)
			+ spcalc->sprite_height * size_l / 2;
		tex_y = ((d * info->texture[TEX_SPRITE].h)
			/ spcalc->sprite_height) / size_l;
		color = get_color(info, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			info->buf[y][stripe] = color;
		y++;
	}
}

void		draw_sprite_stripe(t_info *info, t_spcalc *spcalc, int stripe)
{
	int tex_x;

	tex_x = (int)(info->texture[TEX_SPRITE].size_l
		* (stripe - (-spcalc->sprite_width / 2 + spcalc->sprite_screen_x))
		* info->texture[TEX_SPRITE].w / spcalc->sprite_width)
		/ info->texture[TEX_SPRITE].size_l;
	if (0 < spcalc->transform.y && 0 <= stripe
	&& stripe <= info->screen.w && spcalc->transform.y < info->z_buffer[stripe])
		draw_sprite_stripe_imple(info, spcalc, tex_x, stripe);
}
