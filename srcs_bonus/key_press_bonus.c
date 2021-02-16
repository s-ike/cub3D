/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:50:38 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/16 17:54:39 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		x_close(info);
	else if (key == KEY_W)
		set_vals_for_2intvars(&info->keys.w, &info->keys.s, 1, 0);
	else if (key == KEY_S)
		set_vals_for_2intvars(&info->keys.s, &info->keys.w, 1, 0);
	else if (key == KEY_A)
		set_vals_for_2intvars(&info->keys.a, &info->keys.d, 1, 0);
	else if (key == KEY_D)
		set_vals_for_2intvars(&info->keys.d, &info->keys.a, 1, 0);
	else if (key == KEY_LEFT)
		set_vals_for_2intvars(&info->keys.left, &info->keys.right, 1, 0);
	else if (key == KEY_RIGHT)
		set_vals_for_2intvars(&info->keys.right, &info->keys.left, 1, 0);
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == KEY_ESC)
		x_close(info);
	else if (key == KEY_W)
		info->keys.w = 0;
	else if (key == KEY_S)
		info->keys.s = 0;
	else if (key == KEY_A)
		info->keys.a = 0;
	else if (key == KEY_D)
		info->keys.d = 0;
	else if (key == KEY_LEFT)
		info->keys.left = 0;
	else if (key == KEY_RIGHT)
		info->keys.right = 0;
	return (0);
}
