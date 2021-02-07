/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/07 23:11:15 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: 画面サイズ
// TODO: cubfileの初期位置が0,0だと、(0,0)だと初期位置がない、と判断しているので、no start positionエラーが出る
// エラー文を変えるか、フラグを作ってその値をみる

void	draw(t_info *info)
{
	for (int y = 0; y < info->screen.h; y++)
	{
		for (int x = 0; x < info->screen.w; x++)
		{
			info->img.data[y * info->screen.w + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int		main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

int		main(int argc, char **argv)
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
	{
		set_window(&info);
		mlx_loop_hook(info.mlx, main_loop, &info);
		mlx_hook(info.win, KEY_PRESS, 1L << KEY_PRESS_MASK, key_press, &info);
		mlx_hook(info.win, KEY_RELEASE, 1L << KEY_RELEASE_MASK, key_release, &info);
		mlx_hook(info.win, BTN_X, 1L << STRUCTURE_NOTIFY_MASK, x_close, &info);
		mlx_loop(info.mlx);
	}
	else if (info.mode == SAVEMODE)
	{
		calc(&info);
		if (create_bmp(&info.img, info.buf, &info.screen) < 0)
			exitsave_with_errmsg(ERR_BMP, &info);
		exitsave(&info);
	}
	return (0);
}
