/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 01:47:51 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:23:49 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_LIST_BONUS_H
# define SPRITE_LIST_BONUS_H

# include <stdlib.h>
# include "libft.h"

typedef struct	s_splist
{
	int				x;
	int				y;
	double			distance;
	struct s_splist	*next;
}				t_splist;

t_splist		*splst_new(int x, int y);
void			splist_add_front(t_splist **list, t_splist *new);
t_splist		*splist_sort(t_splist *head);
void			splist_clear(t_splist **list);

#endif
