/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 20:55:31 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/14 02:15:30 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft.h"
# include "struct_mlximg_bonus.h"
# include "struct_screen_bonus.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif
# define MAX_FD 256

# define GNL_ERROR -1
# define GNL_EOF 0
# define GNL_EXIST 1

# define ERR -1
# define SUCCESS 0

# define BMP_NAME "cub3D.bmp"
# define BMP_HEADER_SIZE 14
# define BMP_INFOHEADER_SIZE 40
# define BMP_OFFSET 4
# define ARGB_SIZE 4
# define BMP_MAGIC "BM"
# define BMP_PLANES 1
# define BMP_COMPRESSION 0
# define BMP_SIZE 32

/*
** util.c
*/
void	safe_free(char **ptr);
int		str_isdigit(const char *s);
int		chrcount(const char *s, char c);
void	set_vals_for_2intvars(int *v1, int *v2, int n1, int n2);
/*
** get_line.c
*/
int		get_next_line(int fd, char **line);
/*
** bitmap.c
*/
int		create_bmp(t_mlximg *img, int **buf, t_screen *screen);

#endif
