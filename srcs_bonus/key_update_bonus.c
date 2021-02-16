/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:51:33 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/16 17:54:45 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_bool
	can_move_x(t_info *info, double x)
{
	double x2;

	x2 = 2 * x;
	if (info->map[(int)(info->pos_x + x * MOVE_SPEED)][(int)info->pos_y]
		!= CHECKED_WALL
	&& info->map[(int)(info->pos_x + x2 * MOVE_SPEED)][(int)info->pos_y]
		!= CHECKED_WALL)
		return (TRUE);
	return (FALSE);
}

static t_bool
	can_move_y(t_info *info, double y)
{
	double	y2;

	y2 = 2 * y;
	if (info->map[(int)info->pos_x][(int)(info->pos_y + y * MOVE_SPEED)]
		!= CHECKED_WALL
	&& info->map[(int)info->pos_x][(int)(info->pos_y + y2 * MOVE_SPEED)]
		!= CHECKED_WALL)
		return (TRUE);
	return (FALSE);
}

static void
	move(t_info *info, t_direction dir)
{
	double	x;
	double	y;

	x = 0.0;
	if (dir == SOUTH || dir == NORTH)
		x = dir == SOUTH ? -info->dir_x : info->dir_x;
	else if (dir == WEST || dir == EAST)
		x = dir == WEST ? -info->plane_x : info->plane_x;
	if (can_move_x(info, x) == TRUE)
		info->pos_x += x * MOVE_SPEED;
	y = 0.0;
	if (dir == SOUTH || dir == NORTH)
		y = dir == SOUTH ? -info->dir_y : info->dir_y;
	else if (dir == WEST || dir == EAST)
		y = dir == WEST ? -info->plane_y : info->plane_y;
	if (can_move_y(info, y) == TRUE)
		info->pos_y += y * MOVE_SPEED;
}

static void
	rotation(t_info *info, t_bool is_left)
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

int	key_update(t_info *info)
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
