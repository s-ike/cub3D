/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 00:39:58 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/25 17:55:10 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "key_map.h"
# include "sprite_list.h"
# include "utils.h"
# include "cub3d_error.h"
# include "mlx.h"

# define PRG_NAME "cub3D"
# define CUBFILE_EXT ".cub"
# define XPM_EXT ".xpm"
# ifdef LINUX
#  define C_RED "\e[31m"
#  define C_DEF "\e[0m"
# else
#  define C_RED "\x1b[31m"
#  define C_DEF "\x1b[0m"
# endif
# define GAMEMODE 2
# define SAVEMODE 3
# define MAP_W 24
# define MAP_H 33
# define TEX_W 64
# define TEX_H 64
# ifdef LINUX
#  define MOVE_SPEED 0.01
# else
#  define MOVE_SPEED 0.05
# endif
# define ROT_SPEED MOVE_SPEED

enum			e_settings
{
	SETTING_R,
	SETTING_NO,
	SETTING_SO,
	SETTING_WE,
	SETTING_EA,
	SETTING_S,
	SETTING_F,
	SETTING_C,
};

enum			e_texdir
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST,
	TEX_SPRITE,
	TEX_END,
};

typedef enum	s_bool
{
	FALSE,
	TRUE,
}				t_bool;

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

typedef struct	s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	right;
	int	left;
}				t_keys;

typedef struct	s_info
{
	int			screen_w;
	int			screen_h;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	t_keys		keys;
	t_img		img;
	int			**buf;
	double		*z_buffer;
	t_splist	*splist;
	int			**texture;
	uint32_t	floor_color;
	uint32_t	ceilling_color;
	int			fd;
}				t_info;

/*
** key.c
*/
int				x_close(t_info *info);
int				key_update(t_info *info);
int				key_press(int key, t_info *info);
int				key_release(int key, t_info *info);

#endif
