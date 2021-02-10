/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:54:10 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/10 16:57:10 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_calc(t_info *info, t_spcalc *spcalc,
						int sprite_x, int sprite_y)
{
	double inv_det;

	spcalc->sprite.x = sprite_x + 0.5 - info->pos_x;
	spcalc->sprite.y = sprite_y + 0.5 - info->pos_y;
	inv_det = 1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y);
	spcalc->transform.x = inv_det * (info->dir_y * spcalc->sprite.x
										- info->dir_x * spcalc->sprite.y);
	spcalc->transform.y = inv_det * (-info->plane_y * spcalc->sprite.x
										+ info->plane_x * spcalc->sprite.y);
	spcalc->sprite_screen_x =
		(int)((info->screen.w / 2)
			* (1 + spcalc->transform.x / spcalc->transform.y));
	spcalc->v_move_screen = 0;
}

static void	calc_for_drawing(t_info *info, t_spcalc *spcalc)
{
	spcalc->sprite_height = (int)fabs((info->screen.h / spcalc->transform.y) / V_DIV);
	spcalc->draw_start_y = -spcalc->sprite_height / 2
		+ info->screen.h / 2 + spcalc->v_move_screen;
	if (spcalc->draw_start_y < 0)
		spcalc->draw_start_y = 0;
	spcalc->draw_end_y = spcalc->sprite_height / 2
		+ info->screen.h / 2 + spcalc->v_move_screen;
	if (spcalc->draw_end_y >= info->screen.h)
		spcalc->draw_end_y = info->screen.h;
	spcalc->sprite_width = (int)fabs(info->screen.h / spcalc->transform.y / U_DIV);
	spcalc->draw_start_x = -spcalc->sprite_width / 2 + spcalc->sprite_screen_x;
	if (spcalc->draw_start_x < 0)
		spcalc->draw_start_x = 0;
	spcalc->draw_end_x = spcalc->sprite_width / 2 + spcalc->sprite_screen_x;
	if (spcalc->draw_end_x >= info->screen.w)
		spcalc->draw_end_x = info->screen.w;
}

static void	draw_sprite(t_info *info, int sprite_x, int sprite_y)
{
	t_spcalc	spcalc;
	int			stripe;

	init_calc(info, &spcalc, sprite_x, sprite_y);
	calc_for_drawing(info, &spcalc);
	stripe = spcalc.draw_start_x;
	while (stripe < spcalc.draw_end_x)
	{
		draw_sprite_stripe(info, &spcalc, stripe);
		stripe++;
	}
}

void		sprite_casting(t_info *info)
{
	t_splist	*sp_head;

	sp_head = info->splist;
	while (sp_head)
	{
		sp_head->distance =
			((info->pos_x - (sp_head->x + 0.5))
			* (info->pos_x - (sp_head->x + 0.5))
			+ (info->pos_y - (sp_head->y + 0.5))
			* (info->pos_y - (sp_head->y + 0.5)));
		sp_head = sp_head->next;
	}
	info->splist = splist_sort(info->splist);
	sp_head = info->splist;
	while (sp_head)
	{
		if (sp_head->distance < 0.03)
		{
			sp_head = sp_head->next;
			continue ;
		}
		draw_sprite(info, sp_head->x, sp_head->y);
		sp_head = sp_head->next;
	}
}
