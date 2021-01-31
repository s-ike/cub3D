/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:17:34 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/01 00:38:01 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERROR_H
# define CUB3D_ERROR_H

# define ERR_MSG 			"Error"
# define ERR_CUBFILE_EXT	"Invalid file extension"
# define ERR_CUBFILE		"Invalid cub file"
# define ERR_CUBFILE_R		"Invalid resolution"
# define ERR_CUBFILE_NO		"Invalid north texture"
# define ERR_CUBFILE_SO		"Invalid south texture"
# define ERR_CUBFILE_WE		"Invalid west texture"
# define ERR_CUBFILE_EA		"Invalid east texture"
# define ERR_CUBFILE_S		"Invalid sprite texture"
# define ERR_CUBFILE_F		"Invalid floor color"
# define ERR_CUBFILE_C		"Invalid ceilling color"
# define ERR_MAP			"Invalid map"
# define ERR_BIG_MAP		"Invalid map (too big)"
# define ERR_CHR_MAP		"Invalid map (invalid characters)"
# define ERR_NO_POS			"Invalid map (no start position)"
# define ERR_OPEN_MAP		"Invalid map (unclosed)"
# define ERR_GNL			"An error occurred while running gnl"
# define ERR_BMP			"An error occurred while creating the bitmap"
# define ERR_CUB			"An error occurred while running cub3D"

#endif
