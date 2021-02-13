/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 02:47:16 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 10:37:04 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_info(t_info *info)
{
	int	i;

	if (info->z_buffer)
		free(info->z_buffer);
	i = -1;
	while (++i < info->screen.h)
		free(info->buf[i]);
	splist_clear(&info->splist);
	mlx_destroy_image(info->mlx, info->img.img);
	i = -1;
	while (++i < TEX_END)
		mlx_destroy_image(info->mlx, info->texture[i].img);
	mlx_destroy_display(info->mlx);
	free(info->buf);
}

void		freegame(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	free_info(info);
	free(info->mlx);
}

void		freesave(t_info *info)
{
	free_info(info);
	free(info->mlx);
}

void		put_errmsg(t_errmsg msg)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(ERR_MSG, STDERR_FILENO);
	ft_putstr_fd(C_DEF, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
