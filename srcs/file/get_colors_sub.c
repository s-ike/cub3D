/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:20:45 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/20 19:20:57 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor_color(t_info *info, int r, int g, int b)
{
	info->floor_color = r;
	info->floor_color <<= 8;
	info->floor_color |= g;
	info->floor_color <<= 8;
	info->floor_color |= b;
}

void	set_ceilling_color(t_info *info, int r, int g, int b)
{
	info->ceilling_color = r;
	info->ceilling_color <<= 8;
	info->ceilling_color |= g;
	info->ceilling_color <<= 8;
	info->ceilling_color |= b;
}
