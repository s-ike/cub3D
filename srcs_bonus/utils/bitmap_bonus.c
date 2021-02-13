/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:01:57 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:17:48 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

static int	write_image_data(int fd, int **buf, t_screen *screen)
{
	int	*line;
	int	i;
	int	j;

	if (!(line = (int *)malloc(screen->w * sizeof(int))))
		return (ERR);
	i = screen->h - 1;
	while (0 <= i)
	{
		j = 0;
		while (j < screen->w)
		{
			line[j] = buf[i][j];
			j++;
		}
		write(fd, line, screen->w * sizeof(int));
		i--;
	}
	free(line);
	line = NULL;
	return (SUCCESS);
}

static void	write_info_header(int fd, t_screen *screen, int bpp, int image_size)
{
	uint32_t	infoheader_size;
	uint16_t	plane;
	uint32_t	compression;
	uint32_t	zero;

	infoheader_size = BMP_INFOHEADER_SIZE;
	write(fd, &infoheader_size, 4);
	write(fd, &screen->w, 4);
	write(fd, &screen->h, 4);
	plane = BMP_PLANES;
	write(fd, &plane, 2);
	if (BMP_SIZE < bpp)
		bpp = BMP_SIZE;
	write(fd, &bpp, 2);
	compression = BMP_COMPRESSION;
	write(fd, &compression, 4);
	write(fd, &image_size, 4);
	zero = 0;
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

static void	write_file_header(int fd, int file_size, int header_size)
{
	uint32_t	zero;

	zero = 0;
	write(fd, BMP_MAGIC, 2);
	write(fd, &file_size, 4);
	write(fd, &zero, 4);
	write(fd, &header_size, 4);
}

int			create_bmp(t_mlximg *img, int **buf, t_screen *screen)
{
	int	fd;
	int	header_size;
	int	file_size;
	int	image_size;

	if ((fd = open(BMP_NAME, O_WRONLY | O_CREAT, 0755)) < 0)
		return (ERR);
	image_size = (((ARGB_SIZE * screen->w) * screen->h) / 8);
	header_size = BMP_HEADER_SIZE + BMP_INFOHEADER_SIZE;
	file_size = header_size + image_size;
	write_file_header(fd, file_size, header_size);
	write_info_header(fd, screen, img->bpp, image_size);
	if (write_image_data(fd, buf, screen) < 0)
	{
		close(fd);
		return (ERR);
	}
	close(fd);
	return (SUCCESS);
}
