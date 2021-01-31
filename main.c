/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/01 00:13:05 by sikeda           ###   ########.fr       */
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
				{
					splist_clear(&info->splist);
					exit(EXIT_FAILURE);
				}
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
			// int	texY = (int)texPos & (info->texture[texNum].h - 1);
			int	texY = (int)texPos;
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

t_bool	load_image(t_info *info, t_mlximg *texture, char *filename)
{
	if (!(texture->img = mlx_xpm_file_to_image(info->mlx, filename, &texture->w, &texture->h)))
		return (FALSE);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_l, &texture->endian);
	return (TRUE);
}

t_bool	load_texture(t_info *info, int tex_num, char *filename)
{
	return (load_image(info, &info->texture[tex_num], filename));
}

t_errmsg	validate_filename(char *filename, char *type)
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

t_errmsg	validate_readable_file(char *filename, t_info *info)
{
	char	buf;

	if ((info->fd = open(filename, O_RDONLY)) < 0)
		return (strerror(errno));
	if (read(info->fd, &buf, 0) < 0)
		return (strerror(errno));
	return (NULL);
}

t_errmsg	get_resolution(t_info *info, int *settings, char **split)
{
	// t_screen	current;

	if (!split[1] || !split[2] || split[3] || *settings & (1 << SETTING_R))
		return (ERR_CUBFILE_R);
	if (!str_isdigit(split[1]) || !str_isdigit(split[2]))
		return (ERR_CUBFILE_R);
	info->screen.w = ft_atoi(split[1]);
	info->screen.h = ft_atoi(split[2]);
	if (info->screen.w <= 0 || info->screen.h <= 0)
		return (ERR_CUBFILE_R);
	// TODO: macの古いライブラリでは対応していないので開発用にコメント
	// mlx_get_screen_size(info->mlx, &current.w, &current.h);
	// if (current.w < info->screen.w)
	// 	info->screen.w = current.w;
	// if (current.h < info->screen.h)
	// 	info->screen.h = current.h;
	*settings |= (1 << SETTING_R);
	return (NULL);
}

static t_bool	validate_texture(int *settings, char **split, int flg)
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

t_errmsg	get_no_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_NO) == FALSE)
		return (ERR_CUBFILE_NO);
	if (load_texture(info, TEX_NORTH, split[1]) == FALSE)
		return (ERR_CUBFILE_NO);
	*settings |= (1 << SETTING_NO);
	return (NULL);
}

t_errmsg	get_so_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_SO) == FALSE)
		return (ERR_CUBFILE_SO);
	if (load_texture(info, TEX_SOUTH, split[1]) == FALSE)
		return (ERR_CUBFILE_SO);
	*settings |= (1 << SETTING_SO);
	return (NULL);
}

t_errmsg	get_we_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_WE) == FALSE)
		return (ERR_CUBFILE_WE);
	if (load_texture(info, TEX_WEST, split[1]) == FALSE)
		return (ERR_CUBFILE_WE);
	*settings |= (1 << SETTING_WE);
	return (NULL);
}

t_errmsg	get_ea_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_EA) == FALSE)
		return (ERR_CUBFILE_EA);
	if (load_texture(info, TEX_EAST, split[1]) == FALSE)
		return (ERR_CUBFILE_EA);
	*settings |= (1 << SETTING_EA);
	return (NULL);
}

t_errmsg	get_sprite_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_S) == FALSE)
		return (ERR_CUBFILE_S);
	if (load_texture(info, TEX_SPRITE, split[1]) == FALSE)
		return (ERR_CUBFILE_S);
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
	return (0 <= n && n <= EIGHT_BIT_MAX);
}

void	set_floor_color(t_info *info, int r, int g, int b)
{
	info->floor_color = r;
	info->floor_color <<= 8;
	info->floor_color |= g;
	info->floor_color <<= 8;
	info->floor_color |= b;
}

void	set_ceilling_color(t_info *info, int r, int g, int b)
{
	info->ceilling_color = r;
	info->ceilling_color <<= 8;
	info->ceilling_color |= g;
	info->ceilling_color <<= 8;
	info->ceilling_color |= b;
}

t_bool	get_color(t_info *info, char **split, int flg)
{
	char	**colors;
	t_bool	ret;

	ret = TRUE;
	if (!split[1] || split[2])
		return (FALSE);
	if (chrcount(split[1], ',') != 2)
		return (FALSE);
	colors = ft_split(split[1], ',');
	if (!colors[0] || !colors[1] || !colors[2] || colors[3]
	|| !str_isdigit(colors[0])
	|| !str_isdigit(colors[1])
	|| !str_isdigit(colors[2])
	|| !is_uint8_range(ft_atoi(colors[0]))
	|| !is_uint8_range(ft_atoi(colors[1]))
	|| !is_uint8_range(ft_atoi(colors[2])))
		ret = FALSE;
	if (ret == TRUE && flg == SETTING_F)
		set_floor_color(info, ft_atoi(colors[0]),
							ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (ret == TRUE && flg == SETTING_C)
		set_ceilling_color(info, ft_atoi(colors[0]),
							ft_atoi(colors[1]), ft_atoi(colors[2]));
	clear_split(&colors);
	return (ret);
}

t_errmsg	get_floor_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_F))
		return (ERR_CUBFILE_F);
	if (get_color(info, split, SETTING_F) == FALSE)
		return (ERR_CUBFILE_F);
	*settings |= (1 << SETTING_F);
	return (NULL);
}

t_errmsg	get_ceilling_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_C))
		return (ERR_CUBFILE_C);
	if (get_color(info, split, SETTING_C) == FALSE)
		return (ERR_CUBFILE_C);
	*settings |= (1 << SETTING_C);
	return (NULL);
}

t_errmsg	get_setting_val(t_info *info, int *settings, char **split)
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

t_bool		is_map_size_too_large(size_t len, int line_num)
{
	if (COL < len || ROW < line_num)
		return (TRUE);
	return (FALSE);
}

t_bool		is_map_with_only_correct_chr(t_info *info, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strchr(" 012NSEW", line[i]))
		{
			if (ft_strchr("NSEW", line[i]))
			{
				if (info->pos_x == 0.0 && info->pos_y == 0.0)
				{
					info->pos_x = (double)info->map_line_num + 0.49;
					info->pos_y = i + 0.49;
					info->map_start_dir = line[i];
				}
				else
					return (FALSE);
			}
		}
		else
			return (FALSE);
	return (TRUE);
}

t_bool		has_start_position(int x, int y)
{
	if (x == 0 && y == 0)
		return (FALSE);
	return (TRUE);
}

t_errmsg	is_closed_map(t_info *info, int row, int col)
{
	t_errmsg	msg;

	msg = NULL;
	if (info->map[row][col] == CHECKED_WALL
	|| info->map[row][col] == CHECKED_SPRITE
	|| info->map[row][col] == CHECKED_FLOOR)
		return (NULL);
	if (info->map[row][col] == WALL)
	{
		info->map[row][col] = CHECKED_WALL;
		return (NULL);
	}
	else if (info->map[row][col] == SPRITE)
		info->map[row][col] = CHECKED_SPRITE;
	else
		info->map[row][col] = CHECKED_FLOOR;
	if (row <= 0 || info->map_line_num <= row || col <= 0 || COL <= col)
		return (ERR_OPEN_MAP);
	if ((msg = is_closed_map(info, row + 1, col)))
		return (msg);
	if ((msg = is_closed_map(info, row - 1, col)))
		return (msg);
	if ((msg = is_closed_map(info, row, col + 1)))
		return (msg);
	if ((msg = is_closed_map(info, row, col - 1)))
		return (msg);
	return (NULL);
}

t_errmsg	validate_map(t_info *info)
{
	if (has_start_position((int)info->pos_x, (int)info->pos_y) == FALSE)
		return (ERR_NO_POS);
	return (is_closed_map(info, (int)info->pos_x, (int)info->pos_y));
}

t_errmsg	get_map(t_info *info, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (is_map_size_too_large(len, info->map_line_num + 1) == TRUE)
		return (ERR_BIG_MAP);
	if (is_map_with_only_correct_chr(info, line) == FALSE)
		return (ERR_CHR_MAP);
	ft_strlcpy(info->map[info->map_line_num], line, len + 1);
	info->map_line_num++;
	return (NULL);
}

t_errmsg	parse_line(t_info *info, int *settings, char *line)
{
	static t_bool	has_started_reading_map;
	static t_bool	has_finished_reading_map;
	char			**split;
	t_errmsg		msg;

	if (!line)
		return (ERR_GNL);
	if (!*line)
	{
		if (has_started_reading_map == TRUE)
			has_finished_reading_map = TRUE;
		return (NULL);
	}
	msg = NULL;
	if (*settings == EIGHT_BIT_MAX && ft_strchr(" 012NSEW", *line))
	{
		if (has_finished_reading_map == TRUE)
			return (ERR_MAP);
		has_started_reading_map = TRUE;
		return (get_map(info, line));
	}
	else if (*settings != EIGHT_BIT_MAX)
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

t_errmsg	parse_file(t_info *info)
{
	t_errmsg	msg;
	char		*line;
	int			exists;
	int			setting_flg;

	msg = NULL;
	setting_flg = 0;
	exists = 1;
	while (GNL_EOF <= (exists = get_next_line(info->fd, &line)) && !msg)
	{
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
#include <stdio.h>	// debug
t_errmsg	parse_arg(int argc, char **argv, t_info *info)
{
	t_errmsg	msg;

	if (argc == GAMEMODE)
		info->mode = GAMEMODE;
	else if (argc == SAVEMODE && ft_strcmp(argv[SAVEMODE - 1], "--save") == 0)
		info->mode = SAVEMODE;
	else
		return (strerror(EINVAL));
	info->fd = -1;
	msg = NULL;
	msg = validate_filename(argv[1], CUBFILE_EXT);
	if (!msg)
		msg = validate_readable_file(argv[1], info);
	if (!msg)
		msg = parse_file(info);
	if (!msg)
		ft_bzero(info->map[info->map_line_num], COL + 1);
	if (!msg)
		msg = validate_map(info);
	// debug
	for (int y = 0; y < info->map_line_num; y++)
	{
		for (int x = 0; info->map[y][x] != '\0'; x++)
		{
			printf("%c", info->map[y][x]);
		}
		printf("\n");
	}
	if (info->fd != -1)
		close(info->fd);
	return (msg);
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
			exit_with_errmsg_and_free(ERR_BMP, &info);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
