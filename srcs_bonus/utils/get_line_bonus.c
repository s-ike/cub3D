/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:32:56 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:17:43 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

static ssize_t	read_fd(int fd, char **buff, char **str, char **find)
{
	char	*tmp;
	ssize_t	read_count;

	while ((0 <= (read_count = read(fd, *buff, BUFFER_SIZE))))
	{
		(*buff)[read_count] = '\0';
		if (*str == NULL)
			*str = ft_strdup(*buff);
		else
		{
			tmp = *str;
			*str = ft_strjoin(*str, *buff);
			safe_free(&tmp);
		}
		if ((*find = ft_strchr(*str, '\n')) || !read_count || !*str)
			break ;
	}
	return (read_count);
}

static int		make_line(char **str, char **find, char **line)
{
	char	*tmp;
	int		result;

	result = GNL_EXIST;
	if (*find)
	{
		*line = ft_substr(*str, 0, *find - *str);
		tmp = *str;
		if (!(*str = ft_strdup(*str + (*find - *str) + 1)))
			result = GNL_ERROR;
		safe_free(&tmp);
	}
	else
	{
		*line = ft_strdup(*str);
		safe_free(str);
		result = GNL_EOF;
	}
	if (!*line || result == GNL_ERROR)
	{
		safe_free(line);
		safe_free(str);
		result = GNL_ERROR;
	}
	return (result);
}

int				get_next_line(int fd, char **line)
{
	static char	*strs[MAX_FD];
	char		*buff;
	char		*find;
	ssize_t		read_count;

	if (line)
		*line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || MAX_FD <= fd)
		return (GNL_ERROR);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line || !buff || read(fd, buff, 0) < 0)
	{
		safe_free(&strs[fd]);
		safe_free(&buff);
		return (GNL_ERROR);
	}
	find = NULL;
	read_count = read_fd(fd, &buff, &strs[fd], &find);
	safe_free(&buff);
	if (!strs[fd])
		return (GNL_ERROR);
	if (!find && read_count == 0)
		find = ft_strchr(strs[fd], '\n');
	return (make_line(&strs[fd], &find, line));
}
