/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:58:09 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/14 00:41:21 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	floor_casting(t_info *info)
{
	int	y;
	int	x;

	y = info->screen.h / 2 + 1;
	while (y < info->screen.h)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// 左端の光線（x = 0）と右端の光線（x = w）のrayDir
		float rayDirX0 = info->dir_x - info->plane_x;	// dirX:-1, planeX:0
		float rayDirY0 = info->dir_y - info->plane_y;	// dirY:0, planeY:0.66
		float rayDirX1 = info->dir_x + info->plane_x;	// dirX:-1, planeX:0
		float rayDirY1 = info->dir_y + info->plane_y;	// dirY:0, planeY:0.66

		// Current y position compared to the center of the screen (the horizon)
		// 画面の中心（地平線）と比較した現在のy位置
		int p = y - info->screen.h / 2;	// 画面の最下部からスタート

		// Vertical position of the camera.
		// カメラの垂直位置
		float posZ = 0.5 * info->screen.h;	// スクリーンの真ん中

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		// 現在の行のカメラから床までの水平距離。
		// 0.5は、床と天井のちょうど真ん中のz位置です。
		float rowDistance = posZ / p;	//初期-1, 次-1.00418413

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		// 各x（カメラ平面に平行）に追加する必要のある実世界のステップベクトルを計算します。
		// ステップバイステップで追加すると、内部ループでの重みによる乗算が回避されます。
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / info->screen.w;	//初期-0
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / info->screen.w;	//初期-0.00206249999

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		// 左端の列の実世界の座標。 これは、右に進むにつれて更新されます。
		float floorX = info->pos_x + rowDistance * rayDirX0;	//初期23, 次23.0041847
		float floorY = info->pos_y + rowDistance * rayDirY0;	//初期12.15..., 次12.1627617

		x = -1;
		while (++x < info->screen.w)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			// セル座標はfloorXとfloorYの整数部分から単純に取得されます
			int cellX = (int)floorX;	//初期23
			int cellY = (int)floorY;	//初期12

			// get the texture coordinate from the fractional part
			// 小数部分からテクスチャ座標を取得します
			int f_tx = (int)(info->texture[TEX_FLOOR].w * (floorX - cellX)) & (info->texture[TEX_FLOOR].w - 1);	//初期0
			int f_ty = (int)(info->texture[TEX_FLOOR].h * (floorY - cellY)) & (info->texture[TEX_FLOOR].h - 1);	//初期10
			int c_tx = (int)(info->texture[TEX_CEILLING].w * (floorX - cellX)) & (info->texture[TEX_FLOOR].w - 1);	//初期0
			int c_ty = (int)(info->texture[TEX_CEILLING].h * (floorY - cellY)) & (info->texture[TEX_FLOOR].h - 1);	//初期10

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int color;

			// floor
			color = info->texture[TEX_FLOOR].data[info->texture[TEX_FLOOR].w * f_ty + f_tx];
			// color = (color >> 1) & 8355711; // make a bit darker
			info->buf[y][x] = color;

			// ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[TEX_CEILLING].data[info->texture[TEX_CEILLING].w * c_ty + c_tx];
			// color = (color >> 1) & 8355711; // make a bit darker
			info->buf[info->screen.h - y - 1][x] = color;
		}
		y++;
	}
}
