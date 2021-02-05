/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:56:09 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 01:56:10 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_errmsg	get_setting_val(t_info *info, int *settings, char **split)
{
	if (ft_strcmp(split[0], "R") == 0)
		return (get_resolution(info, settings, split));
	if (ft_strcmp(split[0], "NO") == 0)
		return (get_no_texture(info, settings, split));
	if (ft_strcmp(split[0], "SO") == 0)
		return (get_so_texture(info, settings, split));
	if (ft_strcmp(split[0], "WE") == 0)
		return (get_we_texture(info, settings, split));
	if (ft_strcmp(split[0], "EA") == 0)
		return (get_ea_texture(info, settings, split));
	if (ft_strcmp(split[0], "S") == 0)
		return (get_sprite_texture(info, settings, split));
	if (ft_strcmp(split[0], "F") == 0)
		return (get_floor_color(info, settings, split));
	if (ft_strcmp(split[0], "C") == 0)
		return (get_ceilling_color(info, settings, split));
	return (ERR_CUBFILE);
}

t_errmsg		get_settings(t_info *info, int *settings, char *line)
{
	t_errmsg	msg;
	char		**split;

	msg = NULL;
	split = ft_split(line, ' ');
	msg = get_setting_val(info, settings, split);
	clear_split(&split);
	return (msg);
}
