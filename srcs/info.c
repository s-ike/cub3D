/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:14:08 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/25 23:22:36 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	allocate_textures_buf(t_info *info)
{
	int	i;
	int	j;

	if (!(info->texture = (int **)malloc(sizeof(int *) * TEX_END)))
		return (exit_with_errmsg(strerror(errno)));
	i = -1;
	while (++i < TEX_END)
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W))))
			return (exit_with_errmsg(strerror(errno)));
	i = -1;
	while (++i < TEX_END)
	{
		j = -1;
		while (++j < TEX_H * TEX_W)
			info->texture[i][j] = 0;
	}
}

void		set_info(t_info *info)
{
	info->mlx = mlx_init();
	info->pos_x = 22.0;
	info->pos_y = 5.5;
	info->dir_x = -1.0;
	info->dir_y = 0.0;
	info->plane_x = 0.0;
	info->plane_y = 0.66;
	ft_bzero(&info->keys, sizeof(t_keys));
	info->splist = NULL;
	info->map_line_num = 0;
	allocate_textures_buf(info);
}

void		set_buffer(t_info *info)
{
	int	i;
	int	j;

	if (!(info->z_buffer = (double *)malloc(info->screen_w * sizeof(double))))
		return (exit_with_errmsg(strerror(errno)));
	if (!(info->buf = (int **)malloc(info->screen_h * sizeof(int *))))
		return (exit_with_errmsg(strerror(errno)));
	i = -1;
	while (++i < info->screen_h)
		if (!(info->buf[i] = (int *)malloc(info->screen_w * sizeof(int))))
			return (exit_with_errmsg(strerror(errno)));
	i = -1;
	while (++i < info->screen_h)
	{
		j = -1;
		while (++j < info->screen_w)
			info->buf[i][j] = 0;
	}
}

void		set_window(t_info *info)
{
	info->win = mlx_new_window(
		info->mlx, info->screen_w, info->screen_h, PRG_NAME);
	info->img.img = mlx_new_image(info->mlx, info->screen_w, info->screen_h);
	info->img.data = (int *)mlx_get_data_addr(
		info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}
