/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:34:16 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 01:57:25 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_floor_color(t_info *info, int r, int g, int b)
{
	info->floor_color = r;
	info->floor_color <<= 8;
	info->floor_color |= g;
	info->floor_color <<= 8;
	info->floor_color |= b;
}

static void		set_ceilling_color(t_info *info, int r, int g, int b)
{
	info->ceilling_color = r;
	info->ceilling_color <<= 8;
	info->ceilling_color |= g;
	info->ceilling_color <<= 8;
	info->ceilling_color |= b;
}

static t_bool	get_color(t_info *info, char **split, int flg)
{
	char	**colors;
	t_bool	ret;

	ret = TRUE;
	if (!split[1] || split[2])
		return (FALSE);
	if (chrcount(split[1], ',') != 2)
		return (FALSE);
	colors = ft_split(split[1], ',');
	if (!colors[0] || !colors[1] || !colors[2] || colors[3]
	|| !str_isdigit(colors[0])
	|| !str_isdigit(colors[1])
	|| !str_isdigit(colors[2])
	|| !is_uint8_range(ft_atoi(colors[0]))
	|| !is_uint8_range(ft_atoi(colors[1]))
	|| !is_uint8_range(ft_atoi(colors[2])))
		ret = FALSE;
	if (ret == TRUE && flg == SETTING_F)
		set_floor_color(info, ft_atoi(colors[0]),
							ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (ret == TRUE && flg == SETTING_C)
		set_ceilling_color(info, ft_atoi(colors[0]),
							ft_atoi(colors[1]), ft_atoi(colors[2]));
	clear_split(&colors);
	return (ret);
}

t_errmsg		get_floor_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_F))
		return (ERR_CUBFILE_F);
	if (get_color(info, split, SETTING_F) == FALSE)
		return (ERR_CUBFILE_F);
	*settings |= (1 << SETTING_F);
	return (NULL);
}

t_errmsg		get_ceilling_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_C))
		return (ERR_CUBFILE_C);
	if (get_color(info, split, SETTING_C) == FALSE)
		return (ERR_CUBFILE_C);
	*settings |= (1 << SETTING_C);
	return (NULL);
}
