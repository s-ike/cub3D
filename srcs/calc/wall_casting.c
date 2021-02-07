#include "cub3d.h"

void	wall_casting(t_info *info)
{
	int	x;

	x = 0;
	while (x < info->screen.w)
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

		x++;
	}
}
