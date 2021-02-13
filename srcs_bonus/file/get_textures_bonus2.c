/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:38:31 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/14 00:09:11 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_errmsg	get_floor_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_F) == FALSE)
		return (ERR_CUBFILE_F);
	if (load_texture(info, TEX_FLOOR, split[1]) == FALSE)
		return (ERR_CUBFILE_F);
	*settings |= (1 << SETTING_F);
	return (NULL);
}

t_errmsg	get_ceilling_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_C) == FALSE)
		return (ERR_CUBFILE_C);
	if (load_texture(info, TEX_CEILLING, split[1]) == FALSE)
		return (ERR_CUBFILE_C);
	*settings |= (1 << SETTING_C);
	return (NULL);
}
