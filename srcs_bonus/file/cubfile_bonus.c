/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:43:51 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/20 17:27:09 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_errmsg	parse_line(t_info *info, int *settings, char *line)
{
	static t_bool	has_started_reading_map;
	static t_bool	has_finished_reading_map;
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
		return (get_settings(info, settings, line));
	else
		return (ERR_CUBFILE);
	return (msg);
}

static t_errmsg	parse_file(t_info *info)
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
	safe_free(&line);
	if (exists == GNL_ERROR)
		return (ERR_GNL);
	if (msg)
		get_next_line(info->fd, NULL);
	return (msg);
}

t_errmsg		parse_arg(int argc, char **argv, t_info *info)
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
	msg = validate_readable_file(argv[1], &info->fd);
	if (!msg)
		msg = parse_file(info);
	if (!msg)
		ft_bzero(info->map[info->map_line_num], COL + 1);
	if (!msg)
		msg = validate_map(info);
	close(info->fd);
	return (msg);
}
