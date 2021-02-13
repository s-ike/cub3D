/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_sub_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:57:31 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:22:39 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_color(t_info *info, int tex_x, int tex_y)
{
	return (info->texture[TEX_SPRITE].data[
				info->texture[TEX_SPRITE].w * tex_y + tex_x]);
}

void		draw_sprite_stripe(t_info *info, t_spcalc *spcalc, int stripe)
{
	int tex_x;
	int	tex_y;
	int	color;
	int	y;
	int	d;

	tex_x = (int)(256
		* (stripe - (-spcalc->sprite_width / 2 + spcalc->sprite_screen_x))
		* info->texture[TEX_SPRITE].w / spcalc->sprite_width) / 256;
	if (0 < spcalc->transform.y && 0 <= stripe
	&& stripe <= info->screen.w && spcalc->transform.y < info->z_buffer[stripe])
	{
		y = spcalc->draw_start_y;
		while (y < spcalc->draw_end_y)
		{
			d = y * 256 - info->screen.h * 128 + spcalc->sprite_height * 128;
			tex_y = ((d * info->texture[TEX_SPRITE].h)
				/ spcalc->sprite_height) / 256;
			color = get_color(info, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				info->buf[y][stripe] = color;
			y++;
		}
	}
}