/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/03 02:15:35 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: 画面サイズ

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

void	calc(t_info *info)
{
	//FLOOR CASTING
	int	y = info->screen.h / 2 + 1;
	while (y < info->screen.h)
	{
		int	x = -1;
		while (++x < info->screen.w)
		{
			info->buf[y][x] = info->floor_color;
			info->buf[info->screen.h - y - 1][x] = info->ceilling_color;
		}
		y++;
	}
	// WALL CASTING
	for (int x = 0; x < info->screen.w; x++)
	{
		//calculate ray position and direction
		//光線の位置と方向を計算します
		double	cameraX	= 2 * x / (double)info->screen.w - 1;	//カメラ空間のx座標	//初期-1
		double	rayDirX = info->dir_x + info->plane_x * cameraX;	//初期-1
		double	rayDirY = info->dir_y + info->plane_y * cameraX;	//初期-0.66000

		//which box of the map we're in
		 //マップのどのボックスにいるのか
		int	mapX = (int)info->pos_x;	//初期22
		int	mapY = (int)info->pos_y;	//初期11

		//length of ray from current position to next x or y-side
		//現在の位置から次のxまたはy側までの光線の長さ
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//1つのxまたはy側から次のxまたはy側までの光線の長さ
		double	deltaDistX = fabs(1 / rayDirX);	//初期1
		double	deltaDistY = fabs(1 / rayDirY);	//初期1.51515
		double	perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		//xまたはy方向（+1または-1）にステップする方向
		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->pos_x - mapX) * deltaDistX;	//初期0
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->pos_y - mapY) * deltaDistY;	//初期0.757575
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->pos_y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			t_splist	*new;

			//jump to next map square, OR in x-direction, OR in y-direction
			//次のマップの正方形にジャンプ、OR x方向、OR y方向
			if (sideDistX < sideDistY)	//ループ1
			{
				sideDistX += deltaDistX;	//初期1
				mapX += stepX;	//初期21, 20, 19, ...
				side = 0;
			}
			else	//ループ1
			{
				sideDistY += deltaDistY;	//初期2.27272
				mapY += stepY;	//初期10, 9, ...
				side = 1;
			}
			//Check if ray has hit a wall
			if (info->map[mapX][mapY] == CHECKED_SPRITE && !info->spmap[mapX][mapY])
			{
				info->spmap[mapX][mapY] = 1;
				if (!(new = splst_new(mapX, mapY)))
					exitgame_with_errmsg(ERR_CUB, info);
				splist_add_front(&info->splist, new);
			}
			if (info->map[mapX][mapY] == CHECKED_WALL)	//初期[21][11]
				hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		//垂直光線の距離を計算します（ユークリッド距離は魚眼効果を与えます！）
		if (side == 0)
			perpWallDist = (mapX - info->pos_x + (1 - stepX) / 2) / rayDirX;	//初期(mapX(18)-pos_x(22)+(1-stepX(-1))/2)/rayDirX(-1) = 3
		else
			perpWallDist = (mapY - info->pos_y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		//画面に描画する線の高さを計算します
		int	lineHeight = (int)(info->screen.h / perpWallDist);	//初期160

		//calculate lowest and highest pixel to fill in current stripe
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStart = -lineHeight / 2 + info->screen.h / 2;	//初期160
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + info->screen.h / 2;	//初期320
		if (drawEnd >= info->screen.h)
			drawEnd = info->screen.h - 1;

		int	texNum;
		if (side)
			texNum = rayDirY < 0 ? TEX_WEST : TEX_EAST;
		else
			texNum = rayDirX < 0 ? TEX_NORTH : TEX_SOUTH;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit	//壁が正確に当たった場所
		if (side == 0)
			wallX = info->pos_y + perpWallDist * rayDirY;	//初期9.519999
		else
			wallX = info->pos_x + perpWallDist * rayDirX;
		wallX -= floor(wallX);	// floor(): 小数点以下の切り捨て -=しているので小数部分を取り出している

		//x coordinate on the texture
		//テクスチャのx座標
		int texX = (int)(wallX * (double)info->texture[texNum].w);
		if (side == 0 && rayDirX > 0)
			texX = info->texture[texNum].w - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = info->texture[texNum].w - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		// 画面ピクセルあたりのテクスチャ座標をどれだけ増やすか
		double step = 1.0 * info->texture[texNum].h / lineHeight;	//初期0.4
		// Starting texture coordinate
		// テクスチャ座標の開始
		double texPos = (drawStart - info->screen.h / 2 + lineHeight / 2) * step;	//初期0
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			//テクスチャ座標を整数にキャストし、オーバーフローの場合は（texHeight-1）でマスクします
			int	texY = (int)fmin((int)texPos, (info->texture[texNum].h - 1));
			texPos += step;
			int	color = info->texture[texNum].data[info->texture[texNum].h * texY + texX];
			info->buf[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->z_buffer[x] = perpWallDist;	//perpendicular distance is used 垂直距離が使用されます
	}

	//SPRITE CASTING
	//sort sprites from far to close スプライトを遠いものから近いものに並べ替える
	t_splist	*sp_head;
	sp_head = info->splist;
	// for (int i = 0; i < NUM_SPRITES; i++)
	// {
	// 	g_spriteOrder[i] = i;
	// 	g_spriteDistance[i] = ((info->pos_x - g_sprite[i].x) * (info->pos_x - g_sprite[i].x) + (info->pos_y - g_sprite[i].y) * (info->pos_y - g_sprite[i].y));	//sqrt not taken, unneeded 三角関数で現在位置とスプライト位置で作る三角形の斜辺を計算
	// }
	// sortSprites(g_spriteOrder, g_spriteDistance, NUM_SPRITES);
	while (sp_head)
	{
		sp_head->distance = ((info->pos_x - (sp_head->x + 0.5)) * (info->pos_x - (sp_head->x + 0.5)) + (info->pos_y - (sp_head->y + 0.5)) * (info->pos_y - (sp_head->y + 0.5)));	//sqrt not taken, unneeded 三角関数で現在位置とスプライト位置で作る三角形の斜辺を計算
		sp_head = sp_head->next;
	}
	info->splist = splist_sort(info->splist);

	//after sorting the sprites, do the projection and draw them
	//スプライトを並べ替えた後、投影を実行して描画します
	// for (int i = 0; i < NUM_SPRITES; i++)
	sp_head = info->splist;
	while (sp_head)
	{
		if (sp_head->distance < 0.03)
		{
			sp_head = sp_head->next;
			continue ;
		}
		//translate sprite position to relative to camera
		//スプライトの位置をカメラの相対位置に変換します
		// double spriteX = g_sprite[g_spriteOrder[i]].x + 0.5 - info->pos_x;
		// double spriteY = g_sprite[g_spriteOrder[i]].y + 0.5 - info->pos_y;
		double spriteX = sp_head->x + 0.5 - info->pos_x;
		double spriteY = sp_head->y + 0.5 - info->pos_y;

		//transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

		double invDet = 1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y);	//required for correct matrix multiplication 正しい行列乗算に必要

		double transformX = invDet * (info->dir_y * spriteX - info->dir_x * spriteY);
		double transformY = invDet * (-info->plane_y * spriteX + info->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(g_spriteDistance[i])

		int spriteScreenX = (int)((info->screen.w / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		//画面上のスプライトの高さを計算します
		int spriteHeight = (int)fabs((info->screen.h / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye //実際の距離の代わりに「transformY」を使用すると、魚眼レンズが防止されます
		//calculate lowest and highest pixel to fill in current stripe
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStartY = -spriteHeight / 2 + info->screen.h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + info->screen.h / 2 + vMoveScreen;
		if (drawEndY >= info->screen.h)
			drawEndY = info->screen.h;

		//calculate width of the sprite
		int spriteWidth = (int)fabs(info->screen.h / transformY / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= info->screen.w)
			drawEndX = info->screen.w;

		//loop through every vertical stripe of the sprite on screen
		//画面上のスプライトのすべての垂直ストライプをループします
		for (int stripe =  drawStartX; stripe < drawEndX; stripe++)
		{
			// debug
			if (sp_head != NULL && sp_head->next == NULL)
			{
				double dis;

				dis = sp_head->distance;
			}
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * info->texture[TEX_SPRITE].w / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (0 < transformY && 0 <= stripe && stripe <= info->screen.w && transformY < info->z_buffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe 現在のストライプのすべてのピクセルに対して
				{
					int d = (y-vMoveScreen) * 256 - info->screen.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats 浮動小数点数を回避するための256および128の係数
					int texY = ((d * info->texture[TEX_SPRITE].h) / spriteHeight) / 256;
					int color = info->texture[TEX_SPRITE].data[info->texture[TEX_SPRITE].w * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color ピクセルが黒でない場合はペイントし、黒は非表示の色です
				}
		}
		sp_head = sp_head->next;
	}
}

int		main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

int	main(int argc, char **argv)
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
