/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 02:47:16 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/21 12:24:45 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void
	free_info(t_info *info, t_bool without_texs)
{
	int	i;

	if (info->z_buffer)
		free(info->z_buffer);
	i = -1;
	while (++i < info->screen.h)
		if (info->buf && info->buf[i])
			free(info->buf[i]);
	splist_clear(&info->splist);
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	i = -1;
	while (without_texs == FALSE && ++i < TEX_END)
		if (info->texture[i].img)
			mlx_destroy_image(info->mlx, info->texture[i].img);
	if (without_texs == FALSE)
		mlx_destroy_display(info->mlx);
	if (info->buf)
		free(info->buf);
}

void
	free_without_textures(t_info *info)
{
	free_info(info, TRUE);
	free(info->mlx);
}

void
	freegame(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	free_info(info, FALSE);
	free(info->mlx);
}

void
	freesave(t_info *info)
{
	free_info(info, FALSE);
	free(info->mlx);
}

void
	put_errmsg(t_errmsg msg)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(ERR_MSG, STDERR_FILENO);
	ft_putstr_fd(C_DEF, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
