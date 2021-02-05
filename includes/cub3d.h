/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 00:39:58 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 01:41:51 by sikeda           ###   ########.fr       */
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
# include "struct_mlximg.h"
# include "struct_screen.h"
# ifdef LINUX
#  include "../minilibx-linux/mlx.h"
# else
#  include "../mlx/mlx.h"
# endif

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
# define ROW 64
# define COL 64
# ifdef LINUX
#  define MOVE_SPEED 0.01
# else
#  define MOVE_SPEED 0.05
# endif
# define ROT_SPEED MOVE_SPEED
# define EIGHT_BIT_MAX 0xff
# define WALL '1'
# define SPRITE '2'
# define CHECKED_WALL '!'
# define CHECKED_SPRITE '@'
# define CHECKED_FLOOR '#'
# ifdef LINUX
#  define MLX_DESTROY_DISPLAY(mlx) (mlx_destroy_display(mlx))
# else
#  define MLX_DESTROY_DISPLAY(mlx) ((void)(mlx))
# endif

# define SET_A1_B0(a, b) ((a) = 1, (b) = 0)

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

typedef enum	e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}				t_direction;

typedef enum	e_bool
{
	FALSE,
	TRUE,
}				t_bool;

typedef	char*	t_errmsg;

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
	t_screen	screen;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	t_keys		keys;
	t_mlximg	img;
	int			**buf;
	double		*z_buffer;
	t_splist	*splist;
	t_mlximg	texture[TEX_END];
	uint32_t	floor_color;
	uint32_t	ceilling_color;
	int			fd;
	char		map[ROW + 1][COL + 1];
	int			spmap[ROW][COL];
	int			map_line_num;
	char		map_start_dir;
	int			mode;
}				t_info;

/*
** info.c
*/
void			set_info(t_info *info);
void			set_camera(t_info *info);
void			set_buffer(t_info *info);
void			set_mlximg(t_info *info);
void			set_window(t_info *info);
/*
** close.c
*/
int				x_close(t_info *info);
/*
** exit.c
*/
void			exitsave(t_info *info);
void			exitsave_with_errmsg(t_errmsg msg, t_info *info);
void			exitgame(t_info *info);
void			exitgame_with_errmsg(t_errmsg msg, t_info *info);
void			exit_with_errmsg(t_errmsg msg);
/*
** exit_sub.c
*/
void			freegame(t_info *info);
void			freesave(t_info *info);
void			put_errmsg(t_errmsg msg);
/*
** key.c
*/
int				x_close(t_info *info);
int				key_update(t_info *info);
int				key_press(int key, t_info *info);
int				key_release(int key, t_info *info);
/*
** cubfile.c
*/
t_errmsg		parse_arg(int argc, char **argv, t_info *info);
/*
** file_util.c
*/
t_errmsg		validate_filename(char *filename, char *type);
t_errmsg		validate_readable_file(char *filename, int *fd);
void			clear_split(char ***split);
/*
** get_settings.c
*/
t_errmsg		get_setting_val(t_info *info, int *settings, char **split);
/*
** get_resolution.c
*/
t_errmsg		get_resolution(t_info *info, int *settings, char **split);
/*
** get_textures.c
*/
t_errmsg		get_no_texture(t_info *info, int *settings, char **split);
t_errmsg		get_so_texture(t_info *info, int *settings, char **split);
t_errmsg		get_we_texture(t_info *info, int *settings, char **split);
t_errmsg		get_ea_texture(t_info *info, int *settings, char **split);
t_errmsg		get_sprite_texture(t_info *info, int *settings, char **split);
/*
** get_colors.c
*/
t_errmsg		get_ceilling_color(t_info *info, int *settings, char **split);
t_errmsg		get_floor_color(t_info *info, int *settings, char **split);
/*
** map.c
*/
t_errmsg		get_map(t_info *info, char *line);
/*
** map_validation.c
*/
t_errmsg		validate_map(t_info *info);

#endif
