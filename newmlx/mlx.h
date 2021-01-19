/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:39:54 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/19 23:39:57 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

/*
**  needed before everything else.
**  return (void *)0 if failed
*/
void			*mlx_init();

/*
** Basic actions
*/
/*
**  return void *0 if failed
*/
void			*mlx_new_window(void *mlx_ptr, int size_x,
									int size_y, char *title);
int				mlx_clear_window(void *mlx_ptr, void *win_ptr);
/*
**  origin for x & y is top left corner of the window
**  y down is positive
**  color is 0xAARRGGBB format
**  x and y must fit into the size of the window,
** no control is done on the values
*/
int				mlx_pixel_put(void *mlx_ptr, void *win_ptr,
									int x, int y, int color);

/*
** Image stuff
*/
/*
**  return void *0 if failed
*/
void			*mlx_new_image(void *mlx_ptr, int width, int height);
/*
**  endian : 0 = graphical sever is little endian, 1 = big endian
**  usefull in a network environment where graphical app show on
** a remote monitor that can have a different endian
*/
char			*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
										int *size_line, int *endian);
int				mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
										void *img_ptr, int x, int y);
unsigned int	mlx_get_color_value(void *mlx_ptr, int color);

/*
** dealing with Events
*/
int				mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int				mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int				mlx_expose_hook (void *win_ptr,
									int (*funct_ptr)(), void *param);

int				mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
int				mlx_loop (void *mlx_ptr);

/*
**  hook funct are called as follow :
**   expose_hook(void *param);
**   key_hook(int keycode, void *param);
**   mouse_hook(int button, int x,int y, void *param);
**   loop_hook(void *param);
*/

/*
**  Usually asked...
**   mlx_string_put display may vary in size between OS
** and between mlx implementations
*/

int				mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y,
										int color, char *string);
void			*mlx_xpm_to_image(void *mlx_ptr, char **xpm_data,
										int *width, int *height);
void			*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
										int *width, int *height);
void			*mlx_png_file_to_image(void *mlx_ptr, char *file,
										int *width, int *height);

int				mlx_destroy_window(void *mlx_ptr, void *win_ptr);

int				mlx_destroy_image(void *mlx_ptr, void *img_ptr);

/*
**  generic hook system for all events, and minilibX functions that
**    can be hooked. Some macro and defines from X11/X.h are needed here.
*/

int				mlx_hook(void *win_ptr, int x_event, int x_mask,
							int (*funct)(), void *param);

int				mlx_mouse_hide();
int				mlx_mouse_show();
int				mlx_mouse_move(void *win_ptr, int x, int y);
int				mlx_mouse_get_pos(void *win_ptr, int *x, int *y);

int				mlx_do_key_autorepeatoff(void *mlx_ptr);
int				mlx_do_key_autorepeaton(void *mlx_ptr);
int				mlx_do_sync(void *mlx_ptr);

# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLUSH_CMD 2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

/*
** image_writable can loop forever if no flush occurred.
** Flush is always done by mlx_loop.
** cmd_completed first flush then wait for completion.
** mlx_do_sync equals cmd_completed for all windows.
** cmd is one of the define, param will be img_ptr or win_ptr accordingly
*/
int				mlx_sync(int cmd, void *param);

int				mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

#endif
