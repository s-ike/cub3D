/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/25 15:15:25 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: 解像度によって崩れる

int	g_map[MAP_W][MAP_H] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},	//0
	{1,0,0,0,0,0,2,2,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},	//1
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},	//2
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},	//3
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},	//4
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0},	//5
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},	//6
	{1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0},	//7
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},	//8
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},	//9
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},	//10
	{1,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},	//15
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0},
	{1,1,0,0,0,2,0,0,1,1,2,1,2,1,2,1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
	{1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0},	//20
	{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,'N',0,1,1,1,0},
	{1,1,1,1,0,1,1,1,' ',1,1,1,0,1,0,1,' ',1,0,1,1,1,1,0,1,0,0,0,1,0,0},
	{1,1,1,1,1,1,1,1,' ',1,1,1,1,1,1,1,' ',1,1,1,1,1,1,1,1,1,1,1,1,0,0}
};

int	g_spmap[MAP_W][MAP_H] = {0};

void	exit_with_errmsg(char *msg)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(ERR_MSG, STDERR_FILENO);
	ft_putstr_fd(C_DEF, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	draw(t_info *info)
{
	for (int y = 0; y < info->screen_h; y++)
	{
		for (int x = 0; x < info->screen_w; x++)
		{
			info->img.data[y * info->screen_w + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	int	y = -1;
	while (++y < info->screen_h)
	{
		int	x = -1;
		while (++x < info->screen_w)
		{
			info->buf[y][x] = info->floor_color;
			info->buf[info->screen_h - y - 1][x] = info->ceilling_color;
		}
	}
	// WALL CASTING
	for (int x = 0; x < info->screen_w; x++)
	{
		//calculate ray position and direction
		//光線の位置と方向を計算します
		double	cameraX	= 2 * x / (double)info->screen_w - 1;	//カメラ空間のx座標	//初期-1
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
			if (g_map[mapX][mapY] == 2 && !g_spmap[mapX][mapY])
			{
				g_spmap[mapX][mapY] = 1;
				if (!(new = splst_new(mapX, mapY)))
				{
					splist_clear(&info->splist);
					exit(EXIT_FAILURE);
				}
				splist_add_front(&info->splist, new);
			}
			if (g_map[mapX][mapY] == 1)	//初期[21][11]
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
		int	lineHeight = (int)(info->screen_h / perpWallDist);	//初期160

		//calculate lowest and highest pixel to fill in current stripe
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStart = -lineHeight / 2 + info->screen_h / 2;	//初期160
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + info->screen_h / 2;	//初期320
		if (drawEnd >= info->screen_h)
			drawEnd = info->screen_h - 1;

		int	texNum;
		if (side)
			texNum = rayDirY < 0 ? TEX_EAST : TEX_WEST;
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
		double texPos = (drawStart - info->screen_h / 2 + lineHeight / 2) * step;	//初期0
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			//テクスチャ座標を整数にキャストし、オーバーフローの場合は（texHeight-1）でマスクします
			int	texY = (int)texPos & (TEX_H - 1);
			texPos += step;
			int	color = info->texture[texNum][TEX_H * texY + texX];
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

		int spriteScreenX = (int)((info->screen_w / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		//画面上のスプライトの高さを計算します
		int spriteHeight = (int)fabs((info->screen_h / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye //実際の距離の代わりに「transformY」を使用すると、魚眼レンズが防止されます
		//calculate lowest and highest pixel to fill in current stripe
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStartY = -spriteHeight / 2 + info->screen_h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + info->screen_h / 2 + vMoveScreen;
		if (drawEndY >= info->screen_h)
			drawEndY = info->screen_h;

		//calculate width of the sprite
		int spriteWidth = (int)fabs(info->screen_h / transformY / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= info->screen_w)
			drawEndX = info->screen_w;

		//loop through every vertical stripe of the sprite on screen
		//画面上のスプライトのすべての垂直ストライプをループします
		for (int stripe =  drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_W / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (0 < transformY && 0 <= stripe && stripe <= info->screen_w && transformY < info->z_buffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe 現在のストライプのすべてのピクセルに対して
				{
					int d = (y-vMoveScreen) * 256 - info->screen_h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats 浮動小数点数を回避するための256および128の係数
					int texY = ((d * TEX_H) / spriteHeight) / 256;
					int color = info->texture[TEX_SPRITE][TEX_W * texY + texX]; //get current color from the texture
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

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
		for (int x = 0; x < img->img_width; x++)
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info, int num, char *filename)
{
	t_img	img;

	load_image(info, info->texture[num], filename, &img);
}

void	allocate_textures_buf(t_info *info)
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

void	set_info(t_info *info)
{
	int	i;
	int	j;

	// TODO: 画面サイズ
	// info->mlx = mlx_init();
	info->pos_x = 22.0;
	info->pos_y = 5.5;
	info->dir_x = -1.0;
	info->dir_y = 0.0;
	info->plane_x = 0.0;
	info->plane_y = 0.66;
	ft_bzero(&info->keys, sizeof(t_keys));
	info->move_speed = 0.05;
	info->rot_speed = 0.05;
	info->splist = NULL;
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
	// load_texture(info);
	info->win = mlx_new_window(info->mlx, info->screen_w, info->screen_h, PRG_NAME);
	info->img.img = mlx_new_image(info->mlx, info->screen_w, info->screen_h);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}

char	*validate_filename(char *filename, char *type)
{
	char	*extension;

	if (!ft_strcmp(filename, type))
		return (ERR_CUBFILE_EXT);
	if ((extension = ft_strrchr(filename, '.')))
	{
		if (!ft_strcmp(extension, type))
			return (NULL);
	}
	return (ERR_CUBFILE_EXT);
}

char	*validate_readable_file(char *filename, t_info *info)
{
	char	buf;

	if ((info->fd = open(filename, O_RDONLY)) < 0)
		return (strerror(errno));
	if (read(info->fd, &buf, 0) < 0)
		return (strerror(errno));
	return (NULL);
}

char	*get_resolution(t_info *info, int *settings, char **split)
{
	if (!split[1] || !split[2] || split[3] || *settings & (1 << SETTING_R))
		return (ERR_CUBFILE_R);
	if (!str_isdigit(split[1]) || !str_isdigit(split[2]))
		return (ERR_CUBFILE_R);
	// TODO: 大きすぎる解像度調整
	info->screen_w = ft_atoi(split[1]);
	info->screen_h = ft_atoi(split[2]);
	if (info->screen_w <= 0 || info->screen_h <= 0)
		return (ERR_CUBFILE_R);
	*settings |= (1 << SETTING_R);
	return (NULL);
}

static int	validate_texture(int *settings, char **split, int flg)
{
	int	fd;

	if (!split[1] || split[2] || *settings & (1 << flg))
		return (FALSE);
	if (validate_filename(split[1], XPM_EXT))
		return (FALSE);
	if ((fd = open(split[1], O_RDONLY)) < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

char	*get_no_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_NO) == FALSE)
		return (ERR_CUBFILE_NO);
	load_texture(info, TEX_NORTH, split[1]);
	*settings |= (1 << SETTING_NO);
	return (NULL);
}

char	*get_so_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_SO) == FALSE)
		return (ERR_CUBFILE_SO);
	load_texture(info, TEX_SOUTH, split[1]);
	*settings |= (1 << SETTING_SO);
	return (NULL);
}

char	*get_we_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_WE) == FALSE)
		return (ERR_CUBFILE_WE);
	load_texture(info, TEX_WEST, split[1]);
	*settings |= (1 << SETTING_WE);
	return (NULL);
}

char	*get_ea_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_EA) == FALSE)
		return (ERR_CUBFILE_EA);
	load_texture(info, TEX_EAST, split[1]);
	*settings |= (1 << SETTING_EA);
	return (NULL);
}

char	*get_sprite_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_S) == FALSE)
		return (ERR_CUBFILE_S);
	load_texture(info, TEX_SPRITE, split[1]);
	*settings |= (1 << SETTING_S);
	return (NULL);
}

void	clear_split(char ***split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while ((*split)[i])
		i++;
	if (i == 0)
		return ;
	while (0 <= --i)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
}

int	is_uint8_range(int n)
{
	return (0 <= n && n <= 0xff);
}

int	set_floor_color(t_info *info, int r, int g, int b)
{
	if (!is_uint8_range(r) || !is_uint8_range(g) || !is_uint8_range(b))
		return (FALSE);
	info->floor_color = r;
	info->floor_color <<= 8;
	info->floor_color |= g;
	info->floor_color <<= 8;
	info->floor_color |= b;
	return (TRUE);
}

int	set_ceilling_color(t_info *info, int r, int g, int b)
{
	if (!is_uint8_range(r) || !is_uint8_range(g) || !is_uint8_range(b))
		return (FALSE);
	info->ceilling_color = r;
	info->ceilling_color <<= 8;
	info->ceilling_color |= g;
	info->ceilling_color <<= 8;
	info->ceilling_color |= b;
	return (TRUE);
}

int	get_color(t_info *info, char **split, int flg)
{
	char	**colors;
	int		ret;

	ret = TRUE;
	if (!split[1] || split[2])
		return (FALSE);
	colors = ft_split(split[1], ',');
	if (!colors[0] || !colors[1] || !colors[2] || colors[3]
	|| !str_isdigit(colors[0])
	|| !str_isdigit(colors[1])
	|| !str_isdigit(colors[2]))
		ret = FALSE;
	if (ret == TRUE)
	{
		if (flg == SETTING_F && !set_floor_color(info,
					ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2])))
			ret = FALSE;
		else if (flg == SETTING_C && !set_ceilling_color(info,
					ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2])))
			ret = FALSE;
		else
			ret = FALSE;
	}
	clear_split(&colors);
	return (ret);
}

char	*get_floor_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_F))
		return (ERR_CUBFILE_F);
	if (get_color(info, split, SETTING_F))
		return (ERR_CUBFILE_F);
	*settings |= (1 << SETTING_F);
	return (NULL);
}

char	*get_ceilling_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_C))
		return (ERR_CUBFILE_C);
	if (get_color(info, split, SETTING_C))
		return (ERR_CUBFILE_C);
	*settings |= (1 << SETTING_C);
	return (NULL);
}

// split[0] = "R", split[1] = "1920", split[2] = "1080", split[3] = NULL
char	*get_setting_val(t_info *info, int *settings, char **split)
{
	if (ft_strcmp(split[0], "R") == 0)
		return (get_resolution(info, settings, split));
	if (ft_strcmp(split[0], "NO") == 0)
		return (get_no_texture(info, settings, split));
	if (ft_strcmp(split[0], "SO") == 0)
		return (get_so_texture(info, settings, split));
	if (ft_strcmp(split[0], "WE") == 0)
		return (get_we_texture(info, settings, split));
	if (ft_strcmp(split[0], "EA") == 0)
		return (get_ea_texture(info, settings, split));
	if (ft_strcmp(split[0], "S") == 0)
		return (get_sprite_texture(info, settings, split));
	if (ft_strcmp(split[0], "F") == 0)
		return (get_floor_color(info, settings, split));
	if (ft_strcmp(split[0], "C") == 0)
		return (get_ceilling_color(info, settings, split));
	return (ERR_CUBFILE);
}

char	*parse_line(t_info *info, int *settings, char *line)
{
	char	**split;
	char	*msg;

	if (!line)
		return (ERR_GNL);
	if (!*line)
		return (NULL);
	msg = NULL;
	if (*settings == 0xff && ft_strchr(" 012", *line))
	{
		// TODO;
		// map読み取り
		return (msg);
	}
	else if (*settings != 0xff)
	{
		split = ft_split(line, ' ');
		msg = get_setting_val(info, settings, split);
		clear_split(&split);
		return (msg);
	}
	else
		return (ERR_CUBFILE);
	return (msg);
}

char	*parse_file(t_info *info)
{
	char	*msg;
	char	*line;
	int		exists;
	int		setting_flg;

	msg = NULL;
	setting_flg = 0;
	exists = 1;
	while (GNL_EOF <= (exists = get_next_line(info->fd, &line)) && !msg)
	{
		//TODO: map読み込み中にempty line があるとエラー
		msg = parse_line(info, &setting_flg, line);
		safe_free(&line);
		if (exists == GNL_EOF)
			break ;
	}
	if (exists == GNL_ERROR)
	{
		safe_free(&line);
		return (ERR_GNL);
	}
	return (msg);
}

char	*parse_arg(int argc, char **argv, t_info *info)
{
	char	*msg;
	int		mode;

	if (argc == GAMEMODE || argc == SAVEMODE)
		mode = argc == GAMEMODE ? GAMEMODE : SAVEMODE;
	else
		return (strerror(EINVAL));
	info->fd = -1;
	msg = NULL;
	msg = validate_filename(argv[1], CUBFILE_EXT);
	if (!msg)
		msg = validate_readable_file(argv[1], info);
	if (!msg)
		msg = parse_file(info);
	// if (!msg)
	// 	msg = validate_map();
	if (!msg && mode == GAMEMODE)
	{
		return (NULL);
	}
	else if (!msg)
	{
		// --save
		return (NULL);
	}
	if (info->fd != -1)
		close(info->fd);
	return (msg);
}

int	main(int argc, char **argv)
{
	t_info	info;
	char	*msg;

	info.mlx = mlx_init();
	allocate_textures_buf(&info);
	if ((msg = parse_arg(argc, argv, &info)))
		exit_with_errmsg(msg);
	set_info(&info);
	mlx_loop_hook(info.mlx, main_loop, &info);
	mlx_hook(info.win, KEY_PRESS, 1L<<0, key_press, &info);
	mlx_hook(info.win, KEY_RELEASE, 1L<<0, key_release, &info);
	mlx_hook(info.win, EVENT_X_BTN, 1L<<17, x_close, &info);
	mlx_loop(info.mlx);
	return (0);
}