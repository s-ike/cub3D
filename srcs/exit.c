/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:20:06 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/01 00:20:36 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_info(t_info *info)
{
	int	i;

	if (info->z_buffer)
		free(info->z_buffer);
	i = -1;
	while (++i < info->screen.h)
		free(info->buf[i]);
	free(info->buf);
}

static void	put_errmsg(t_errmsg msg)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(ERR_MSG, STDERR_FILENO);
	ft_putstr_fd(C_DEF, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void		exit_with_free(t_info *info)
{
	free_info(info);
	exit(EXIT_SUCCESS);
}

void		exit_with_errmsg(t_errmsg msg)
{
	put_errmsg(msg);
	exit(EXIT_FAILURE);
}

void		exit_with_errmsg_and_free(t_errmsg msg, t_info *info)
{
	put_errmsg(msg);
	free_info(info);
	exit(EXIT_FAILURE);
}
