/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:26:08 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/06 02:05:22 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	has_start_position(int x, int y)
{
	if (x == 0 && y == 0)
		return (FALSE);
	return (TRUE);
}

static t_errmsg	is_closed_map(t_info *info, int row, int col)
{
	t_errmsg	msg;

	msg = NULL;
	if (info->map[row][col] == CHECKED_WALL
	|| info->map[row][col] == CHECKED_SPRITE
	|| info->map[row][col] == CHECKED_FLOOR)
		return (NULL);
	if (info->map[row][col] == WALL && (info->map[row][col] = CHECKED_WALL))
		return (NULL);
	else if (info->map[row][col] == SPRITE)
		info->map[row][col] = CHECKED_SPRITE;
	else
		info->map[row][col] = CHECKED_FLOOR;
	if (row <= 0 || info->map_line_num <= row || col <= 0 || COL <= col)
		return (ERR_OPEN_MAP);
	if ((msg = is_closed_map(info, row + 1, col)))
		return (msg);
	if ((msg = is_closed_map(info, row - 1, col)))
		return (msg);
	if ((msg = is_closed_map(info, row, col + 1)))
		return (msg);
	if ((msg = is_closed_map(info, row, col - 1)))
		return (msg);
	return (NULL);
}

t_errmsg		validate_map(t_info *info)
{
	if (has_start_position((int)info->pos_x, (int)info->pos_y) == FALSE)
		return (ERR_NO_POS);
	return (is_closed_map(info, (int)info->pos_x, (int)info->pos_y));
}
