/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:34:16 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/20 19:21:06 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	is_invalid_format(char **colors)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	return (
		!colors[0] || !colors[1] || !colors[2] || colors[3]
		|| !str_isdigit(colors[0])
		|| !str_isdigit(colors[1])
		|| !str_isdigit(colors[2])
		|| !is_uint8_range(r)
		|| !is_uint8_range(g)
		|| !is_uint8_range(b)
		|| (r && colors[0][0] == '0')
		|| (g && colors[1][0] == '0')
		|| (b && colors[2][0] == '0'));
}

static t_bool
	get_color(t_info *info, char **split, int flg)
{
	char	**colors;
	t_bool	ret;

	ret = TRUE;
	if (!split[1] || split[2])
		return (FALSE);
	if (chrcount(split[1], ',') != 2)
		return (FALSE);
	colors = ft_split(split[1], ',');
	if (is_invalid_format(colors))
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

t_errmsg
	get_floor_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_F))
		return (ERR_CUBFILE_F);
	if (get_color(info, split, SETTING_F) == FALSE)
		return (ERR_CUBFILE_F);
	*settings |= (1 << SETTING_F);
	return (NULL);
}

t_errmsg
	get_ceilling_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_C))
		return (ERR_CUBFILE_C);
	if (get_color(info, split, SETTING_C) == FALSE)
		return (ERR_CUBFILE_C);
	*settings |= (1 << SETTING_C);
	return (NULL);
}
