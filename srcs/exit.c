/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:20:06 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/01 02:32:16 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	freegame(t_info *info)
{
	int	i;

	if (info->z_buffer)
		free(info->z_buffer);
	i = -1;
	while (++i < info->screen.h)
		free(info->buf[i]);
	splist_clear(&info->splist);
	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_image(info->mlx, info->img.img);
	i = -1;
	while (++i < TEX_END)
		mlx_destroy_image(info->mlx, info->texture[i].img);
	MLX_DESTROY_DISPLAY(info->mlx);
	free(info->buf);
	free(info->mlx);
}

static void	freesave(t_info *info)
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
	MLX_DESTROY_DISPLAY(info->mlx);
	free(info->buf);
	free(info->mlx);
}

static void	put_errmsg(t_errmsg msg)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(ERR_MSG, STDERR_FILENO);
	ft_putstr_fd(C_DEF, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void		exitsave(t_info *info)
{
	freesave(info);
	exit(EXIT_SUCCESS);
}

void		exitsave_with_errmsg(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	freesave(info);
	exit(EXIT_FAILURE);
}

void		exitgame(t_info *info)
{
	freegame(info);
	exit(EXIT_SUCCESS);
}

void		exitgame_with_errmsg(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	freegame(info);
	exit(EXIT_FAILURE);
}

void		exit_with_errmsg(t_errmsg msg)
{
	put_errmsg(msg);
	exit(EXIT_FAILURE);
}
