#include "cub3d.h"

void	sprite_casting(t_info *info)
{
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
