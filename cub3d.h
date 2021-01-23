/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 00:39:58 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/24 01:03:56 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "key_map.h"
# ifdef LINUX
#  include "minilibx-linux/mlx.h"
# else
#  include "newmlx/mlx.h"
# endif

# define PRG_NAME "cub3D"
# define SCREEN_W 640
# define SCREEN_H 480
# define MAP_W 24
# define MAP_H 33
# define TEX_W 64
# define TEX_H 64

enum			e_texdir
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST,
	TEX_SPRITE,
	TEX_END,
};

typedef struct	s_splist
{
	int				x;
	int				y;
	double			distance;
	struct s_splist	*next;
}				t_splist;

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
	int			buf[SCREEN_H][SCREEN_W];
	double		z_buffer[SCREEN_W];
	t_splist	*splist;
	int			**texture;
	double		move_speed;
	double		rot_speed;
}				t_info;

#endif
