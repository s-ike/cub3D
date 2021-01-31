/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:20:06 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/01 02:42:33 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		exitsave(t_info *info)
{
	freesave(info);
	exit(EXIT_SUCCESS);
}

void		exitsave_with_errmsg(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	freesave(info);
	exit(EXIT_FAILURE);
}

void		exitgame(t_info *info)
{
	freegame(info);
	exit(EXIT_SUCCESS);
}

void		exitgame_with_errmsg(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	freegame(info);
	exit(EXIT_FAILURE);
}

void		exit_with_errmsg(t_errmsg msg)
{
	put_errmsg(msg);
	exit(EXIT_FAILURE);
}
