/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 00:39:58 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/16 17:56:26 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "key_map_bonus.h"
# include "sprite_list_bonus.h"
# include "utils_bonus.h"
# include "cub3d_error_bonus.h"
# include "struct_mlximg_bonus.h"
# include "struct_screen_bonus.h"
# ifdef LINUX
#  include "../minilibx-linux/mlx.h"
# else
#  include "../minilibx_mms_20200219/mlx.h"
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
	TEX_FLOOR,
	TEX_CEILLING,
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

typedef struct	s_coordinate
{
	double	x;
	double	y;
}				t_coordinate;

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
	int			fd;
	char		map[ROW + 1][COL + 1];
	int			spmap[ROW][COL];
	int			map_line_num;
	char		map_start_dir;
	int			mode;
}				t_info;

typedef struct	s_step
{
	int	x;
	int	y;
}				t_step;

typedef struct	s_wallcalc
{
	double			camera_x;
	int				map_x;
	int				map_y;
	t_coordinate	ray_dir;
	t_coordinate	side_dist;
	t_coordinate	delta_dist;
	double			wall_dist;
}				t_wallcalc;

typedef struct	s_walltex
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	tex_step;
	double	tex_pos;
}				t_walltex;

typedef struct	s_spcalc
{
	t_coordinate	sprite;
	t_coordinate	transform;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
}				t_spcalc;

typedef struct	s_floorcalc
{
	float	ray_dir_x0;
	float	ray_dir_x1;
	float	ray_dir_y0;
	float	ray_dir_y1;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
}				t_floorcalc;

/*
** info_bonus.c
*/
void			set_info(t_info *info);
void			set_camera(t_info *info);
void			set_buffer(t_info *info);
void			set_mlximg(t_info *info);
void			set_window(t_info *info);
/*
** close_bonus.c
*/
int				x_close(t_info *info);
/*
** exit_bonus.c
*/
void			exitsave(t_info *info);
void			exitsave_with_errmsg(t_errmsg msg, t_info *info);
void			exitgame(t_info *info);
void			exitgame_with_errmsg(t_errmsg msg, t_info *info);
void			exit_with_errmsg(t_errmsg msg);
/*
** exit_sub_bonus.c
*/
void			freegame(t_info *info);
void			freesave(t_info *info);
void			put_errmsg(t_errmsg msg);
/*
** close_bonus.c
*/
int				x_close(t_info *info);
/*
** key_press_bonus.c
*/
int				key_press(int key, t_info *info);
int				key_release(int key, t_info *info);
/*
** key_update_bonus.c
*/
int				key_update(t_info *info);
/*
** cubfile_bonus.c
*/
t_errmsg		parse_arg(int argc, char **argv, t_info *info);
/*
** file_util_bonus.c
*/
t_errmsg		validate_filename(char *filename, char *type);
t_errmsg		validate_readable_file(char *filename, int *fd);
void			clear_split(char ***split);
int				is_uint8_range(int n);
/*
** get_settings_bonus.c
*/
t_errmsg		get_settings(t_info *info, int *settings, char *line);
/*
** get_resolution_bonus.c
*/
t_errmsg		get_resolution(t_info *info, int *settings, char **split);
/*
** get_textures_bonus.c
*/
t_errmsg		get_no_texture(t_info *info, int *settings, char **split);
t_errmsg		get_so_texture(t_info *info, int *settings, char **split);
t_errmsg		get_we_texture(t_info *info, int *settings, char **split);
t_errmsg		get_ea_texture(t_info *info, int *settings, char **split);
t_errmsg		get_sprite_texture(t_info *info, int *settings, char **split);
/*
** get_textures_bonus2.c
*/
t_errmsg		get_floor_texture(t_info *info, int *settings, char **split);
t_errmsg		get_ceilling_texture(t_info *info, int *settings, char **split);
/*
** get_textures_sub_bonus.c
*/
t_bool			load_texture(t_info *info, int tex_num, char *filename);
t_bool			validate_texture(int *settings, char **split, int flg);
/*
** map_bonus.c
*/
t_errmsg		get_map(t_info *info, char *line);
/*
** map_validation_bonus.c
*/
t_errmsg		validate_map(t_info *info);
/*
** calc_bonus.c
*/
void			calc(t_info *info);
/*
** floor_casting_bonus.c
*/
void			floor_casting(t_info *info);
/*
** wall_casting_bonus.c
*/
void			wall_casting(t_info *info);
/*
** wall_casting_sub_bonus.c
*/
void			draw_stripe(t_info *info, t_wallcalc *wallcalc,
								int side, int x);
/*
** sprite_casting_bonus.c
*/
void			sprite_casting(t_info *info);
/*
** sprite_casting_sub_bonus.c
*/
void			draw_sprite_stripe(t_info *info, t_spcalc *spcalc, int stripe);
/*
** draw_bonus.c
*/
void			draw(t_info *info);

#endif
