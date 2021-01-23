/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 22:12:13 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/08 17:02:19 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_words(char const *str, char c)
{
	size_t	cnt;

	if (*str == '\0')
		return (0);
	if (c == '\0' && *str)
		return (1);
	cnt = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (!*str)
			break ;
		while (*str && *str != c)
			str++;
		cnt++;
	}
	return (cnt);
}

static int		free_memories_in_strs(char **strs, size_t size)
{
	while (0 < size)
	{
		free(strs[--size]);
		strs[size] = NULL;
	}
	return (0);
}

static int		set_words(char **strs, char const *str, char c)
{
	size_t	i;
	char	*start;
	char	*end;

	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			start = (char *)str;
			end = ft_strchr(str, c);
			strs[i] = !end ? ft_strdup(str) : ft_substr(start, 0, end - start);
			if (!strs[i])
				return (free_memories_in_strs(strs, i));
			i++;
			if (end)
				str += end - start;
			else
				break ;
		}
		else
			str++;
	}
	strs[i] = NULL;
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	if (!(strs = (char **)malloc((cnt_words(s, c) + 1) * sizeof(char *))))
		return (NULL);
	if (!set_words(strs, s, c))
	{
		free(strs);
		strs = NULL;
		return (NULL);
	}
	return (strs);
}
