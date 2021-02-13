/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 10:53:21 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: 画面サイズ

static int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

static void	game_mode(t_info *info)
{
	set_window(info);
	mlx_loop_hook(info->mlx, main_loop, info);
	mlx_hook(info->win, KEY_PRESS, 1L << KEY_PRESS_MASK, key_press, info);
	mlx_hook(info->win, KEY_RELEASE, 1L << KEY_RELEASE_MASK, key_release, info);
	mlx_hook(info->win, BTN_X, 1L << STRUCTURE_NOTIFY_MASK, x_close, info);
	mlx_loop(info->mlx);
}

static void	save_mode(t_info *info)
{
	calc(info);
	if (create_bmp(&info->img, info->buf, &info->screen) < 0)
		exitsave_with_errmsg(ERR_BMP, info);
	exitsave(info);
}

int			main(int argc, char **argv)
{
	t_info		info;
	t_errmsg	msg;

	set_info(&info);
	if ((msg = parse_arg(argc, argv, &info)))
		exit_with_errmsg(msg);
	set_camera(&info);
	set_buffer(&info);
	set_mlximg(&info);
	if (info.mode == GAMEMODE)
		game_mode(&info);
	else if (info.mode == SAVEMODE)
		save_mode(&info);
	return (0);
}
