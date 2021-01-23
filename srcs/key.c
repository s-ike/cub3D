#include "cub3d.h"

extern int	g_map[MAP_W][MAP_H];

int			x_close(t_info *info)
{
	(void)info;
	// TODO; free() if want
	exit(EXIT_SUCCESS);
	return (0);
}

int			key_update(t_info *info)
{
	if (info->keys.w)
	{
		if (g_map[(int)(info->pos_x + info->dir_x * info->move_speed)][(int)info->pos_y] != 1)
			info->pos_x += info->dir_x * info->move_speed;
		if (g_map[(int)info->pos_x][(int)(info->pos_y + info->dir_y * info->move_speed)] != 1)
			info->pos_y += info->dir_y * info->move_speed;
	}
	if (info->keys.s)
	{
		if (g_map[(int)(info->pos_x - info->dir_x * info->move_speed)][(int)info->pos_y] != 1)
			info->pos_x -= info->dir_x * info->move_speed;
		if (g_map[(int)info->pos_x][(int)(info->pos_y - info->dir_y * info->move_speed)] != 1)
			info->pos_y -= info->dir_y * info->move_speed;
	}
	if (info->keys.d)
	{
		if (g_map[(int)(info->pos_x + info->plane_x * info->move_speed)][(int)info->pos_y] != 1)
			info->pos_x += info->plane_x * info->move_speed;
		if (g_map[(int)info->pos_x][(int)(info->pos_y + info->plane_y * info->move_speed)] != 1)
			info->pos_y += info->plane_y * info->move_speed;
	}
	if (info->keys.a)
	{
		if (g_map[(int)(info->pos_x - info->plane_x * info->move_speed)][(int)info->pos_y] != 1)
			info->pos_x -= info->plane_x * info->move_speed;
		if (g_map[(int)info->pos_x][(int)(info->pos_y - info->plane_y * info->move_speed)] != 1)
			info->pos_y -= info->plane_y * info->move_speed;
	}
	if (info->keys.right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dir_x;
		info->dir_x = info->dir_x * cos(-info->rot_speed) - info->dir_y * sin(-info->rot_speed);
		info->dir_y = oldDirX * sin(-info->rot_speed) + info->dir_y * cos(-info->rot_speed);
		double oldPlaneX = info->plane_x;
		info->plane_x = info->plane_x * cos(-info->rot_speed) - info->plane_y * sin(-info->rot_speed);
		info->plane_y = oldPlaneX * sin(-info->rot_speed) + info->plane_y * cos(-info->rot_speed);
	}
	if (info->keys.left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dir_x;
		info->dir_x = info->dir_x * cos(info->rot_speed) - info->dir_y * sin(info->rot_speed);
		info->dir_y = oldDirX * sin(info->rot_speed) + info->dir_y * cos(info->rot_speed);
		double oldPlaneX = info->plane_x;
		info->plane_x = info->plane_x * cos(info->rot_speed) - info->plane_y * sin(info->rot_speed);
		info->plane_y = oldPlaneX * sin(info->rot_speed) + info->plane_y * cos(info->rot_speed);
	}
	return (0);
}

int			key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		x_close(info);
	else if (key == KEY_W)
		info->keys.w = 1;
	else if (key == KEY_S)
		info->keys.s = 1;
	else if (key == KEY_A)
		info->keys.a = 1;
	else if (key == KEY_D)
		info->keys.d = 1;
	else if (key == KEY_LEFT)
		info->keys.left = 1;
	else if (key == KEY_RIGHT)
		info->keys.right = 1;
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
