/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_mlximg.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 20:54:08 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/30 20:57:26 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MLXIMG_H
# define STRUCT_MLXIMG_H

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
