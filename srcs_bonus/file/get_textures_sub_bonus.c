/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_sub_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 02:00:52 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/20 23:38:15 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_bool
	load_image(t_info *info, t_mlximg *texture, char *filename)
{
	if (!(texture->img = mlx_xpm_file_to_image(info->mlx,
										filename, &texture->w, &texture->h)))
		return (FALSE);
	texture->data = (int *)mlx_get_data_addr(texture->img,
							&texture->bpp, &texture->size_l, &texture->endian);
	return (TRUE);
}

t_bool
	load_texture(t_info *info, int tex_num, char *filename)
{
	return (load_image(info, &info->texture[tex_num], filename));
}

t_bool
	validate_texture(int *settings, char **split, int flg)
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
