/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/20 14:47:14 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "key_map.h"
#include "newmlx/mlx.h"

#define SCREEN_W 640
#define SCREEN_H 480
#define MAP_W 24
#define MAP_H 24
#define TEX_W 64
#define TEX_H 64
#define	NUM_SPRITES 19

int	g_floor = 0x00FF0000;
int	g_ceile = 0x0000FF00;

int	g_map[MAP_W][MAP_H] =
{
	{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

struct	s_sprite
{
	double	x;
	double	y;
	int		texture;
};

struct s_sprite	g_sprite[NUM_SPRITES] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

//arrays used to sort the sprites
int		spriteOrder[NUM_SPRITES];
double	spriteDistance[NUM_SPRITES];

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[SCREEN_H][SCREEN_W];
	double	zBuffer[SCREEN_W];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;

typedef struct	s_pair
{
	double	first;
	int		second;
}				t_pair;

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);	//大きい順にする
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void	draw(t_info *info)
{
	for (int y = 0; y < SCREEN_H; y++)
	{
		for (int x = 0; x < SCREEN_W; x++)
		{
			info->img.data[y * SCREEN_W + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	int	y = -1;
	while (++y < SCREEN_H)
	{
		int	x = -1;
		while (++x < SCREEN_W)
		{
			info->buf[y][x] = g_floor;
			info->buf[SCREEN_H - y - 1][x] = g_ceile;
		}
	}
	// WALL CASTING
	for (int x = 0; x < SCREEN_W; x++)
	{
		//calculate ray position and direction
		//光線の位置と方向を計算します
		double	cameraX	= 2 * x / (double)SCREEN_W - 1;	//カメラ空間のx座標	//初期-1
		double	rayDirX = info->dirX + info->planeX * cameraX;	//初期-1
		double	rayDirY = info->dirY + info->planeY * cameraX;	//初期-0.66000

		//which box of the map we're in
		 //マップのどのボックスにいるのか
		int	mapX = (int)info->posX;	//初期22
		int	mapY = (int)info->posY;	//初期11

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
			sideDistX = (info->posX - mapX) * deltaDistX;	//初期0
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;	//初期0.757575
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
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
			if (0 < g_map[mapX][mapY])	//初期[21][11]
				hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		//垂直光線の距離を計算します（ユークリッド距離は魚眼効果を与えます！）
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;	//初期(mapX(18)-posX(22)+(1-stepX(-1))/2)/rayDirX(-1) = 3
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		//画面に描画する線の高さを計算します
		int	lineHeight = (int)(SCREEN_H / perpWallDist);	//初期160

		//calculate lowest and highest pixel to fill in current stripe
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStart = -lineHeight / 2 + SCREEN_H / 2;	//初期160
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_H / 2;	//初期320
		if (drawEnd >= SCREEN_H)
			drawEnd = SCREEN_H - 1;

		//texturing calculations
		int texNum = g_map[mapX][mapY] - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit	//壁が正確に当たった場所
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;	//初期9.519999
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);	// floor(): 小数点以下の切り捨て -=しているので小数部分を取り出している

		//x coordinate on the texture
		//テクスチャのx座標
		int texX = (int)(wallX * (double)TEX_W);
		if (side == 0 && rayDirX > 0)
			texX = TEX_W - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEX_W - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		// 画面ピクセルあたりのテクスチャ座標をどれだけ増やすか
		double step = 1.0 * TEX_H / lineHeight;	//初期0.4
		// Starting texture coordinate
		// テクスチャ座標の開始
		double texPos = (drawStart - SCREEN_H / 2 + lineHeight / 2) * step;	//初期0
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			//テクスチャ座標を整数にキャストし、オーバーフローの場合は（texHeight-1）でマスクします
			int	texY = (int)texPos & (TEX_H - 1);
			texPos += step;
			int	color = info->texture[texNum][TEX_H * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//y-sideの色を暗く（側面と正面とで色を変えている）
			if (side == 1)
				color = (color >> 1) & 8355711;	//8355711->0x7F7F7F
			info->buf[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->zBuffer[x] = perpWallDist;	//perpendicular distance is used 垂直距離が使用されます
	}

	//SPRITE CASTING
	//sort sprites from far to close スプライトを遠いものから近いものに並べ替える
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((info->posX - g_sprite[i].x) * (info->posX - g_sprite[i].x) + (info->posY - g_sprite[i].y) * (info->posY - g_sprite[i].y));	//sqrt not taken, unneeded 三角関数で現在位置とスプライト位置で作る三角形の斜辺を計算
	}
	sortSprites(spriteOrder, spriteDistance, NUM_SPRITES);

	//after sorting the sprites, do the projection and draw them
	//スプライトを並べ替えた後、投影を実行して描画します
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		//translate sprite position to relative to camera
		//スプライトの位置をカメラの相対位置に変換します
		double spriteX = g_sprite[spriteOrder[i]].x - info->posX;
		double spriteY = g_sprite[spriteOrder[i]].y - info->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);	//required for correct matrix multiplication 正しい行列乗算に必要

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((SCREEN_W / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		//画面上のスプライトの高さを計算します
		int spriteHeight = (int)fabs((SCREEN_H / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye //実際の距離の代わりに「transformY」を使用すると、魚眼レンズが防止されます
		//calculate lowest and highest pixel to fill in current stripe
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStartY = -spriteHeight / 2 + SCREEN_H / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + SCREEN_H / 2 + vMoveScreen;
		if (drawEndY >= SCREEN_H)
			drawEndY = SCREEN_H - 1;

		//calculate width of the sprite
		int spriteWidth = (int)fabs(SCREEN_H / transformY / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= SCREEN_W)
			drawEndX = SCREEN_W - 1;

		//loop through every vertical stripe of the sprite on screen
		//画面上のスプライトのすべての垂直ストライプをループします
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_W / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < SCREEN_W && transformY < info->zBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe 現在のストライプのすべてのピクセルに対して
				{
					int d = (y-vMoveScreen) * 256 - SCREEN_H * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats 浮動小数点数を回避するための256および128の係数
					int texY = ((d * TEX_H) / spriteHeight) / 256;
					int color = info->texture[g_sprite[spriteOrder[i]].texture][TEX_W * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color ピクセルが黒でない場合はペイントし、黒は非表示の色です
				}
		}
	}
}

int		main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!g_map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)info->posY])
			info->posX += info->dirX * info->moveSpeed;
		if (!g_map[(int)info->posX][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	if (key == KEY_S)
	{
		if (g_map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)info->posY])
			info->posX -= info->dirX * info->moveSpeed;
		if (!g_map[(int)info->posX][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
		for (int x = 0; x < img->img_width; x++)
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
	load_image(info, info->texture[8], "textures/barrel.xpm", &img);
	load_image(info, info->texture[9], "textures/pillar.xpm", &img);
	load_image(info, info->texture[10], "textures/greenlight.xpm", &img);
}

int	main()
{
	t_info	info;

	info.mlx = mlx_init();
	info.posX = 22.0;
	info.posY = 11.5;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;

	for (int i = 0; i < SCREEN_H; i++)
		for (int j = 0; j < SCREEN_W; j++)
			info.buf[i][j] = 0;

	if (!(info.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	for (int i = 0; i < 11; i++)
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W))))
			return (-1);
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < TEX_H * TEX_W; j++)
			info.texture[i][j] = 0;

	load_texture(&info);

	info.moveSpeed = 0.2;
	info.rotSpeed = 0.2;

	info.win = mlx_new_window(info.mlx, SCREEN_W, SCREEN_H, "mlx");

	info.img.img = mlx_new_image(info.mlx, SCREEN_W, SCREEN_H);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, main_loop, &info);
	mlx_key_hook(info.win, key_press, &info);

	mlx_loop(info.mlx);

	return (0);
}