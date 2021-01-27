/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:14:08 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/27 22:12:45 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	allocate_textures_buf(t_info *info)
// {
// 	int	i;
// 	int	j;

// 	if (!(info->texture = (int **)malloc(sizeof(int *) * TEX_END)))
// 		return (exit_with_errmsg(strerror(errno)));
// 	i = -1;
// 	while (++i < TEX_END)
// 		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W))))
// 			return (exit_with_errmsg(strerror(errno)));
// 	i = -1;
// 	while (++i < TEX_END)
// 	{
// 		j = -1;
// 		while (++j < TEX_H * TEX_W)
// 			info->texture[i][j] = 0;
// 	}
// }

void		set_info(t_info *info)
{
	info->mlx = mlx_init();
	info->pos_x = 0.0;
	info->pos_y = 0.0;
	info->dir_x = 0.0;
	info->dir_y = 0.0;
	info->plane_x = 0.0;
	info->plane_y = 0.0;
	ft_bzero(&info->keys, sizeof(t_keys));
	info->splist = NULL;
	info->map_line_num = 0;
	info->map_start = 0;
	// allocate_textures_buf(info);
}

void		set_camera(t_info *info)
{
	if (info->map_start == 'N' || info->map_start == 'S')
	{
		info->plane_y = (double)info->screen.w / (double)info->screen.h / 2.0;
		if (info->map_start == 'N')
			info->dir_x = -1.0;
		if (info->map_start == 'S')
		{
			info->dir_x = 1.0;
			info->plane_y = 0 - info->plane_y;
		}
	}
	if (info->map_start == 'E' || info->map_start == 'W')
	{
		info->plane_x = (double)info->screen.w / (double)info->screen.h / 2.0;
		if (info->map_start == 'E')
			info->dir_y = 1.0;
		if (info->map_start == 'W')
		{
			info->dir_y = -1.0;
			info->plane_x = 0 - info->plane_x;
		}
	}
}

void		set_buffer(t_info *info)
{
	int	i;
	int	j;

	if (!(info->z_buffer = (double *)malloc(info->screen.w * sizeof(double))))
		return (exit_with_errmsg(strerror(errno)));
	if (!(info->buf = (int **)malloc(info->screen.h * sizeof(int *))))
		return (exit_with_errmsg(strerror(errno)));
	i = -1;
	while (++i < info->screen.h)
		if (!(info->buf[i] = (int *)malloc(info->screen.w * sizeof(int))))
			return (exit_with_errmsg(strerror(errno)));
	i = -1;
	while (++i < info->screen.h)
	{
		j = -1;
		while (++j < info->screen.w)
			info->buf[i][j] = 0;
	}
}

void		set_window(t_info *info)
{
	info->win = mlx_new_window(
		info->mlx, info->screen.w, info->screen.h, PRG_NAME);
	info->img.img = mlx_new_image(info->mlx, info->screen.w, info->screen.h);
	info->img.data = (int *)mlx_get_data_addr(
		info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}
