/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:14:08 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/18 21:44:02 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_info(t_info *info)
{
	int	i;

	info->mlx = mlx_init();
	info->pos_x = 0.0;
	info->pos_y = 0.0;
	info->dir_x = 0.0;
	info->dir_y = 0.0;
	info->plane_x = 0.0;
	info->plane_y = 0.0;
	info->speed = MOVE_SPEED;
	ft_bzero(&info->keys, sizeof(t_keys));
	ft_bzero(&info->screen, sizeof(t_screen));
	info->splist = NULL;
	info->map_line_num = 0;
	info->map_start_dir = 0;
	info->mode = 0;
	info->z_buffer = NULL;
	info->buf = NULL;
	info->img.img = NULL;
	i = -1;
	while (++i < TEX_END)
		ft_bzero(&info->texture[i], sizeof(t_mlximg));
}

void	set_camera(t_info *info)
{
	if (info->map_start_dir == 'N' || info->map_start_dir == 'S')
	{
		info->plane_y = (double)info->screen.w / (double)info->screen.h / 2.0;
		if (info->map_start_dir == 'N')
			info->dir_x = -1.0;
		if (info->map_start_dir == 'S')
		{
			info->dir_x = 1.0;
			info->plane_y = 0 - info->plane_y;
		}
	}
	if (info->map_start_dir == 'E' || info->map_start_dir == 'W')
	{
		info->plane_x = (double)info->screen.w / (double)info->screen.h / 2.0;
		if (info->map_start_dir == 'E')
			info->dir_y = 1.0;
		if (info->map_start_dir == 'W')
		{
			info->dir_y = -1.0;
			info->plane_x = 0 - info->plane_x;
		}
	}
}

void	set_buffer(t_info *info)
{
	int	i;

	if (!(info->z_buffer = (double *)malloc(info->screen.w * sizeof(double))))
		return (exit_with_errmsg(strerror(errno), info));
	if (!(info->buf = (int **)malloc(info->screen.h * sizeof(int *))))
		return (exit_with_errmsg(strerror(errno), info));
	i = -1;
	while (++i < info->screen.h)
		if (!(info->buf[i] = (int *)malloc(info->screen.w * sizeof(int))))
			return (exit_with_errmsg(strerror(errno), info));
	i = -1;
	while (++i < info->screen.h)
		ft_bzero(info->buf[i], info->screen.w * sizeof(int));
	ft_bzero(info->spmap, ROW * COL * sizeof(int));
}

void	set_mlximg(t_info *info)
{
	info->img.img = mlx_new_image(info->mlx, info->screen.w, info->screen.h);
	info->img.data = (int *)mlx_get_data_addr(
		info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}

void	set_window(t_info *info)
{
	info->win = mlx_new_window(
		info->mlx, info->screen.w, info->screen.h, PRG_NAME);
}
