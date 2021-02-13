/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_mlximg_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 20:54:08 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:23:54 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MLXIMG_BONUS_H
# define STRUCT_MLXIMG_BONUS_H

typedef struct	s_mlximg
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		w;
	int		h;
}				t_mlximg;

#endif
