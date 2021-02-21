/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:38:31 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 02:00:15 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_errmsg
	get_no_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_NO) == FALSE)
		return (ERR_CUBFILE_NO);
	if (load_texture(info, TEX_NORTH, split[1]) == FALSE)
		return (ERR_CUBFILE_NO);
	*settings |= (1 << SETTING_NO);
	return (NULL);
}

t_errmsg
	get_so_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_SO) == FALSE)
		return (ERR_CUBFILE_SO);
	if (load_texture(info, TEX_SOUTH, split[1]) == FALSE)
		return (ERR_CUBFILE_SO);
	*settings |= (1 << SETTING_SO);
	return (NULL);
}

t_errmsg
	get_we_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_WE) == FALSE)
		return (ERR_CUBFILE_WE);
	if (load_texture(info, TEX_WEST, split[1]) == FALSE)
		return (ERR_CUBFILE_WE);
	*settings |= (1 << SETTING_WE);
	return (NULL);
}

t_errmsg
	get_ea_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_EA) == FALSE)
		return (ERR_CUBFILE_EA);
	if (load_texture(info, TEX_EAST, split[1]) == FALSE)
		return (ERR_CUBFILE_EA);
	*settings |= (1 << SETTING_EA);
	return (NULL);
}

t_errmsg
	get_sprite_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_S) == FALSE)
		return (ERR_CUBFILE_S);
	if (load_texture(info, TEX_SPRITE, split[1]) == FALSE)
		return (ERR_CUBFILE_S);
	*settings |= (1 << SETTING_S);
	return (NULL);
}
