/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:20:06 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/21 12:02:19 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void
	exitsave(t_info *info)
{
	freesave(info);
	exit(EXIT_SUCCESS);
}

void
	exitsave_with_errmsg(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	freesave(info);
	exit(EXIT_FAILURE);
}

void
	exitgame(t_info *info)
{
	mlx_loop_end(info->mlx);
	freegame(info);
	exit(EXIT_SUCCESS);
}

void
	exitgame_with_errmsg(t_errmsg msg, t_info *info)
{
	mlx_loop_end(info->mlx);
	put_errmsg(msg);
	freegame(info);
	exit(EXIT_FAILURE);
}

void
	exit_with_errmsg(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	if (ft_strnstr(msg, "texture", ft_strlen(msg)))
		free_without_textures(info);
	else
		freesave(info);
	exit(EXIT_FAILURE);
}
