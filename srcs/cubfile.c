#include "cub3d.h"

t_bool	load_image(t_info *info, t_mlximg *texture, char *filename)
{
	if (!(texture->img = mlx_xpm_file_to_image(info->mlx, filename, &texture->w, &texture->h)))
		return (FALSE);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_l, &texture->endian);
	return (TRUE);
}

t_bool	load_texture(t_info *info, int tex_num, char *filename)
{
	return (load_image(info, &info->texture[tex_num], filename));
}

t_errmsg	validate_filename(char *filename, char *type)
{
	char	*extension;

	if (!ft_strcmp(filename, type))
		return (ERR_CUBFILE_EXT);
	if ((extension = ft_strrchr(filename, '.')))
	{
		if (!ft_strcmp(extension, type))
			return (NULL);
	}
	return (ERR_CUBFILE_EXT);
}

t_errmsg	validate_readable_file(char *filename, t_info *info)
{
	char	buf;

	if ((info->fd = open(filename, O_RDONLY)) < 0)
		return (strerror(errno));
	if (read(info->fd, &buf, 0) < 0)
		return (strerror(errno));
	return (NULL);
}

t_errmsg	get_resolution(t_info *info, int *settings, char **split)
{
	// t_screen	current;

	if (!split[1] || !split[2] || split[3] || *settings & (1 << SETTING_R))
		return (ERR_CUBFILE_R);
	if (!str_isdigit(split[1]) || !str_isdigit(split[2]))
		return (ERR_CUBFILE_R);
	info->screen.w = ft_atoi(split[1]);
	info->screen.h = ft_atoi(split[2]);
	if (info->screen.w <= 0 || info->screen.h <= 0)
		return (ERR_CUBFILE_R);
	// TODO: macの古いライブラリでは対応していないので開発用にコメント
	// mlx_get_screen_size(info->mlx, &current.w, &current.h);
	// if (current.w < info->screen.w)
	// 	info->screen.w = current.w;
	// if (current.h < info->screen.h)
	// 	info->screen.h = current.h;
	*settings |= (1 << SETTING_R);
	return (NULL);
}

static t_bool	validate_texture(int *settings, char **split, int flg)
{
	int	fd;

	if (!split[1] || split[2] || *settings & (1 << flg))
		return (FALSE);
	if (validate_filename(split[1], XPM_EXT))
		return (FALSE);
	if ((fd = open(split[1], O_RDONLY)) < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

t_errmsg	get_no_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_NO) == FALSE)
		return (ERR_CUBFILE_NO);
	if (load_texture(info, TEX_NORTH, split[1]) == FALSE)
		return (ERR_CUBFILE_NO);
	*settings |= (1 << SETTING_NO);
	return (NULL);
}

t_errmsg	get_so_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_SO) == FALSE)
		return (ERR_CUBFILE_SO);
	if (load_texture(info, TEX_SOUTH, split[1]) == FALSE)
		return (ERR_CUBFILE_SO);
	*settings |= (1 << SETTING_SO);
	return (NULL);
}

t_errmsg	get_we_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_WE) == FALSE)
		return (ERR_CUBFILE_WE);
	if (load_texture(info, TEX_WEST, split[1]) == FALSE)
		return (ERR_CUBFILE_WE);
	*settings |= (1 << SETTING_WE);
	return (NULL);
}

t_errmsg	get_ea_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_EA) == FALSE)
		return (ERR_CUBFILE_EA);
	if (load_texture(info, TEX_EAST, split[1]) == FALSE)
		return (ERR_CUBFILE_EA);
	*settings |= (1 << SETTING_EA);
	return (NULL);
}

t_errmsg	get_sprite_texture(t_info *info, int *settings, char **split)
{
	if (validate_texture(settings, split, SETTING_S) == FALSE)
		return (ERR_CUBFILE_S);
	if (load_texture(info, TEX_SPRITE, split[1]) == FALSE)
		return (ERR_CUBFILE_S);
	*settings |= (1 << SETTING_S);
	return (NULL);
}

void	clear_split(char ***split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while ((*split)[i])
		i++;
	if (i == 0)
		return ;
	while (0 <= --i)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
}

int	is_uint8_range(int n)
{
	return (0 <= n && n <= EIGHT_BIT_MAX);
}

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

t_bool	get_color(t_info *info, char **split, int flg)
{
	char	**colors;
	t_bool	ret;

	ret = TRUE;
	if (!split[1] || split[2])
		return (FALSE);
	if (chrcount(split[1], ',') != 2)
		return (FALSE);
	colors = ft_split(split[1], ',');
	if (!colors[0] || !colors[1] || !colors[2] || colors[3]
	|| !str_isdigit(colors[0])
	|| !str_isdigit(colors[1])
	|| !str_isdigit(colors[2])
	|| !is_uint8_range(ft_atoi(colors[0]))
	|| !is_uint8_range(ft_atoi(colors[1]))
	|| !is_uint8_range(ft_atoi(colors[2])))
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

t_errmsg	get_floor_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_F))
		return (ERR_CUBFILE_F);
	if (get_color(info, split, SETTING_F) == FALSE)
		return (ERR_CUBFILE_F);
	*settings |= (1 << SETTING_F);
	return (NULL);
}

t_errmsg	get_ceilling_color(t_info *info, int *settings, char **split)
{
	if (*settings & (1 << SETTING_C))
		return (ERR_CUBFILE_C);
	if (get_color(info, split, SETTING_C) == FALSE)
		return (ERR_CUBFILE_C);
	*settings |= (1 << SETTING_C);
	return (NULL);
}

t_errmsg	get_setting_val(t_info *info, int *settings, char **split)
{
	if (ft_strcmp(split[0], "R") == 0)
		return (get_resolution(info, settings, split));
	if (ft_strcmp(split[0], "NO") == 0)
		return (get_no_texture(info, settings, split));
	if (ft_strcmp(split[0], "SO") == 0)
		return (get_so_texture(info, settings, split));
	if (ft_strcmp(split[0], "WE") == 0)
		return (get_we_texture(info, settings, split));
	if (ft_strcmp(split[0], "EA") == 0)
		return (get_ea_texture(info, settings, split));
	if (ft_strcmp(split[0], "S") == 0)
		return (get_sprite_texture(info, settings, split));
	if (ft_strcmp(split[0], "F") == 0)
		return (get_floor_color(info, settings, split));
	if (ft_strcmp(split[0], "C") == 0)
		return (get_ceilling_color(info, settings, split));
	return (ERR_CUBFILE);
}

t_bool		is_map_size_too_large(size_t len, int line_num)
{
	if (COL < len || ROW < line_num)
		return (TRUE);
	return (FALSE);
}

t_bool		is_map_with_only_correct_chr(t_info *info, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strchr(" 012NSEW", line[i]))
		{
			if (ft_strchr("NSEW", line[i]))
			{
				if (info->pos_x == 0.0 && info->pos_y == 0.0)
				{
					info->pos_x = (double)info->map_line_num + 0.49;
					info->pos_y = i + 0.49;
					info->map_start_dir = line[i];
				}
				else
					return (FALSE);
			}
		}
		else
			return (FALSE);
	return (TRUE);
}

t_bool		has_start_position(int x, int y)
{
	if (x == 0 && y == 0)
		return (FALSE);
	return (TRUE);
}

t_errmsg	is_closed_map(t_info *info, int row, int col)
{
	t_errmsg	msg;

	msg = NULL;
	if (info->map[row][col] == CHECKED_WALL
	|| info->map[row][col] == CHECKED_SPRITE
	|| info->map[row][col] == CHECKED_FLOOR)
		return (NULL);
	if (info->map[row][col] == WALL)
	{
		info->map[row][col] = CHECKED_WALL;
		return (NULL);
	}
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

t_errmsg	validate_map(t_info *info)
{
	if (has_start_position((int)info->pos_x, (int)info->pos_y) == FALSE)
		return (ERR_NO_POS);
	return (is_closed_map(info, (int)info->pos_x, (int)info->pos_y));
}

t_errmsg	get_map(t_info *info, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (is_map_size_too_large(len, info->map_line_num + 1) == TRUE)
		return (ERR_BIG_MAP);
	if (is_map_with_only_correct_chr(info, line) == FALSE)
		return (ERR_CHR_MAP);
	ft_strlcpy(info->map[info->map_line_num], line, len + 1);
	info->map_line_num++;
	return (NULL);
}

t_errmsg	parse_line(t_info *info, int *settings, char *line)
{
	static t_bool	has_started_reading_map;
	static t_bool	has_finished_reading_map;
	char			**split;
	t_errmsg		msg;

	if (!line)
		return (ERR_GNL);
	if (!*line)
	{
		if (has_started_reading_map == TRUE)
			has_finished_reading_map = TRUE;
		return (NULL);
	}
	msg = NULL;
	if (*settings == EIGHT_BIT_MAX && ft_strchr(" 012NSEW", *line))
	{
		if (has_finished_reading_map == TRUE)
			return (ERR_MAP);
		has_started_reading_map = TRUE;
		return (get_map(info, line));
	}
	else if (*settings != EIGHT_BIT_MAX)
	{
		split = ft_split(line, ' ');
		msg = get_setting_val(info, settings, split);
		clear_split(&split);
		return (msg);
	}
	else
		return (ERR_CUBFILE);
	return (msg);
}

t_errmsg	parse_file(t_info *info)
{
	t_errmsg	msg;
	char		*line;
	int			exists;
	int			setting_flg;

	msg = NULL;
	setting_flg = 0;
	exists = 1;
	while (GNL_EOF <= (exists = get_next_line(info->fd, &line)) && !msg)
	{
		msg = parse_line(info, &setting_flg, line);
		safe_free(&line);
		if (exists == GNL_EOF)
			break ;
	}
	if (exists == GNL_ERROR)
	{
		safe_free(&line);
		return (ERR_GNL);
	}
	return (msg);
}

t_errmsg	parse_arg(int argc, char **argv, t_info *info)
{
	t_errmsg	msg;

	if (argc == GAMEMODE)
		info->mode = GAMEMODE;
	else if (argc == SAVEMODE && ft_strcmp(argv[SAVEMODE - 1], "--save") == 0)
		info->mode = SAVEMODE;
	else
		return (strerror(EINVAL));
	msg = NULL;
	if ((msg = validate_filename(argv[1], CUBFILE_EXT)))
		return (msg);
	msg = validate_readable_file(argv[1], info);
	if (!msg)
		msg = parse_file(info);
	if (!msg)
		ft_bzero(info->map[info->map_line_num], COL + 1);
	if (!msg)
		msg = validate_map(info);
	close(info->fd);
	return (msg);
}
