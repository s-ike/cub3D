/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:50:38 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:16:01 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move(t_info *info, t_direction dir)
{
	double	x;
	double	y;

	x = 0.0;
	if (dir == SOUTH || dir == NORTH)
		x = dir == SOUTH ? -info->dir_x : info->dir_x;
	else if (dir == WEST || dir == EAST)
		x = dir == WEST ? -info->plane_x : info->plane_x;
	if (info->map[(int)(info->pos_x + x * MOVE_SPEED)][(int)info->pos_y]
			!= CHECKED_WALL)
		info->pos_x += x * MOVE_SPEED;
	y = 0.0;
	if (dir == SOUTH || dir == NORTH)
		y = dir == SOUTH ? -info->dir_y : info->dir_y;
	else if (dir == WEST || dir == EAST)
		y = dir == WEST ? -info->plane_y : info->plane_y;
	if (info->map[(int)info->pos_x][(int)(info->pos_y + y * MOVE_SPEED)]
			!= CHECKED_WALL)
		info->pos_y += y * MOVE_SPEED;
}

static void	rotation(t_info *info, t_bool is_left)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = is_left == TRUE ? ROT_SPEED : -ROT_SPEED;
	old_dir_x = info->dir_x;
	info->dir_x = info->dir_x * cos(rot_speed) - info->dir_y * sin(rot_speed);
	info->dir_y = old_dir_x * sin(rot_speed) + info->dir_y * cos(rot_speed);
	old_plane_x = info->plane_x;
	info->plane_x = info->plane_x * cos(rot_speed)
					- info->plane_y * sin(rot_speed);
	info->plane_y = old_plane_x * sin(rot_speed)
					+ info->plane_y * cos(rot_speed);
}

int			key_update(t_info *info)
{
	if (info->keys.w)
		move(info, NORTH);
	if (info->keys.s)
		move(info, SOUTH);
	if (info->keys.d)
		move(info, EAST);
	if (info->keys.a)
		move(info, WEST);
	if (info->keys.right)
		rotation(info, FALSE);
	if (info->keys.left)
		rotation(info, TRUE);
	return (0);
}

int			key_press(int key, t_info *info)
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

int			key_release(int key, t_info *info)
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
