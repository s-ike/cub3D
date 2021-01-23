/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:15 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/23 18:38:57 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "key_map.h"
#ifdef LINUX
# include "minilibx-linux/mlx.h"
#else
# include "newmlx/mlx.h"
#endif

#define SCREEN_W 640
#define SCREEN_H 480
#define MAP_W 24
#define MAP_H 33
#define TEX_W 64
#define TEX_H 64
#define	NUM_SPRITES 19

enum	e_texdir
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST,
	TEX_SPRITE,
	TEX_END,
};

int	g_floor = 0x00FF0000;
int	g_ceile = 0x0000FF00;

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

typedef struct	s_splist
{
	int				x;
	int				y;
	double			distance;
	struct s_splist	*next;
}				t_splist;

t_splist	*splst_new(int x, int y)
{
	t_splist	*list;

	if (!(list = (t_splist *)malloc(sizeof(t_splist))))
		return (NULL);
	list->x = x;
	list->y = y;
	list->distance = 0.0;
	list->next = NULL;
	return (list);
}

void	splist_add_front(t_splist **list, t_splist *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (0 < len--)
		*ptr++ = c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static t_splist	*splist_merge(t_splist *list1, t_splist *list2)
{
	t_splist	tmp;
	t_splist	*p;

	ft_bzero(&tmp, sizeof(t_splist));
	p = &tmp;
	while (list1 && list2)
	{
		if (list1->distance <= list2->distance)
		{
			p->next = list2;
			p = list2;
			list2 = list2->next;
		} else {
			p->next = list1;
			p = list1;
			list1 = list1->next;
		}
	}
	if (!list1)
		p->next = list2;
	else
		p->next = list1;
	return (tmp.next);
}

t_splist	*splist_sort(t_splist *head)
{
	t_splist	*partition;
	t_splist	*prev;
	t_splist	*back;

	if (!head || !head->next)
		return (head);
	prev = head;
	back = head->next;
	if (back)
		back = back->next;
	while (back && back->next)
	{
		prev = prev->next;
		back = back->next->next;
	}
	partition = prev->next;
	prev->next = NULL;
	return (splist_merge(splist_sort(head), splist_sort(partition)));
}

void	splist_clear(t_splist **list)
{
	t_splist	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		tmp = NULL;
	}
}

//arrays used to sort the sprites
int		g_spriteOrder[NUM_SPRITES];
double	g_spriteDistance[NUM_SPRITES];

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
	t_splist	*splist;
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
	int		i;
	int		last;

	i = 0;
	while (i < amount - 1)
	{
		last = amount - 1;
		for (int j = amount - 1; i < j; j--)
		{
			if (orders[j].first < orders[j - 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j - 1].first;
				orders[j].second = orders[j - 1].second;
				orders[j - 1].first = tmp.first;
				orders[j - 1].second = tmp.second;
				last = j;
			}
		}
		i = last;
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

		int	texNum;
		if (side)
			texNum = rayDirY < 0 ? TEX_EAST : TEX_WEST;
		else
			texNum = rayDirX < 0 ? TEX_NORTH : TEX_SOUTH;

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
			info->buf[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->zBuffer[x] = perpWallDist;	//perpendicular distance is used 垂直距離が使用されます
	}

	//SPRITE CASTING
	//sort sprites from far to close スプライトを遠いものから近いものに並べ替える
	t_splist	*sp_head;
	sp_head = info->splist;
	// for (int i = 0; i < NUM_SPRITES; i++)
	// {
	// 	g_spriteOrder[i] = i;
	// 	g_spriteDistance[i] = ((info->posX - g_sprite[i].x) * (info->posX - g_sprite[i].x) + (info->posY - g_sprite[i].y) * (info->posY - g_sprite[i].y));	//sqrt not taken, unneeded 三角関数で現在位置とスプライト位置で作る三角形の斜辺を計算
	// }
	// sortSprites(g_spriteOrder, g_spriteDistance, NUM_SPRITES);
	while (sp_head)
	{
		sp_head->distance = ((info->posX - sp_head->x) * (info->posX - sp_head->x) + (info->posY - sp_head->y) * (info->posY - sp_head->y));	//sqrt not taken, unneeded 三角関数で現在位置とスプライト位置で作る三角形の斜辺を計算
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
		// double spriteX = g_sprite[g_spriteOrder[i]].x + 0.5 - info->posX;
		// double spriteY = g_sprite[g_spriteOrder[i]].y + 0.5 - info->posY;
		double spriteX = sp_head->x + 0.5 - info->posX;
		double spriteY = sp_head->y + 0.5 - info->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);	//required for correct matrix multiplication 正しい行列乗算に必要

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(g_spriteDistance[i])

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
			drawEndY = SCREEN_H;

		//calculate width of the sprite
		int spriteWidth = (int)fabs(SCREEN_H / transformY / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= SCREEN_W)
			drawEndX = SCREEN_W;

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
			if (0 < transformY && 0 <= stripe && stripe <= SCREEN_W && transformY < info->zBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe 現在のストライプのすべてのピクセルに対して
				{
					int d = (y-vMoveScreen) * 256 - SCREEN_H * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats 浮動小数点数を回避するための256および128の係数
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
	return (0);
}

int	x_close(t_info *info)
{
	(void)info;
	// TODO; free() if want
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{
		double	i;

		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)(info->posX + info->dirX * i)][(int)info->posY] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)(info->posX + info->dirX * i)][(int)info->posY] != 1)
			info->posX += info->dirX * i;
		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)info->posX][(int)(info->posY + info->dirY * i)] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)info->posX][(int)(info->posY + info->dirY * i)] != 1)
			info->posY += info->dirY * i;
	}
	if (key == KEY_S)
	{
		double	i;

		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)(info->posX - info->dirX * i)][(int)info->posY] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)(info->posX - info->dirX * i)][(int)info->posY] != 1)
			info->posX -= info->dirX * i;
		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)info->posX][(int)(info->posY - info->dirY * i)] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)info->posX][(int)(info->posY - info->dirY * i)] != 1)
			info->posY -= info->dirY * i;
	}
	if (key == KEY_D)
	{
		double	i;

		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)(info->posX + info->planeX * i)][(int)info->posY] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)(info->posX + info->planeX * i)][(int)info->posY] != 1)
			info->posX += info->planeX * i;
		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)info->posX][(int)(info->posY + info->planeY * i)] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)info->posX][(int)(info->posY + info->planeY * i)] != 1)
			info->posY += info->planeY * i;
	}
	if (key == KEY_A)
	{
		double	i;

		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)(info->posX - info->planeX * i)][(int)info->posY] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)(info->posX - info->planeX * i)][(int)info->posY] != 1)
			info->posX -= info->planeX * i;
		i = 0.01;
		while (i <= info->moveSpeed)
		{
			if (g_map[(int)info->posX][(int)(info->posY - info->planeY * i)] == 1)
				break ;
			i += 0.1;
		}
		if (g_map[(int)info->posX][(int)(info->posY - info->planeY * i)] != 1)
			info->posY -= info->planeY * i;
	}
	if (key == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	if (key == KEY_LEFT)
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
		x_close(info);
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

	load_image(info, info->texture[TEX_NORTH], "textures/eagle.xpm", &img);
	load_image(info, info->texture[TEX_SOUTH], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[TEX_EAST], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[TEX_WEST], "textures/greystone.xpm", &img);
	load_image(info, info->texture[TEX_SPRITE], "textures/barrel.xpm", &img);
}

int		set_info(t_info *info)
{
	int	i;
	int	j;

	info->mlx = mlx_init();
	// info->posX = 22.0;
	// info->posY = 11.5;
	info->posX = 22.0;
	info->posY = 5.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.2;
	info->rotSpeed = 0.2;
	info->splist = NULL;
	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
			info->buf[i][j] = 0;
	}
	if (!(info->texture = (int **)malloc(sizeof(int *) * TEX_END)))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < TEX_END)
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W))))
			return (EXIT_FAILURE);
	i = -1;
	while (++i < TEX_END)
	{
		j = -1;
		while (++j < TEX_H * TEX_W)
			info->texture[i][j] = 0;
	}
	load_texture(info);
	info->win = mlx_new_window(info->mlx, SCREEN_W, SCREEN_H, "cub3D");
	info->img.img = mlx_new_image(info->mlx, SCREEN_W, SCREEN_H);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
	return (EXIT_SUCCESS);
}

int	main()
{
	t_info	info;

	if (set_info(&info))
		exit(EXIT_FAILURE);
	mlx_loop_hook(info.mlx, main_loop, &info);
	// mlx_key_hook(info.win, key_press, &info);
	mlx_hook(info.win, KEY_PRESS, 1L<<0, key_press, &info);
	mlx_hook(info.win, EVENT_X_BTN, 1L<<17, x_close, &info);
	mlx_loop(info.mlx);
	return (0);
}