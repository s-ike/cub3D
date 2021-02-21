/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 01:48:12 by sikeda            #+#    #+#             */
/*   Updated: 2021/02/13 23:16:22 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite_list_bonus.h"

t_splist
	*splst_new(int x, int y)
{
	t_splist	*list;

	if (!(list = (t_splist *)malloc(sizeof(t_splist))))
		return (NULL);
	list->x = x;
	list->y = y;
	list->distance = 0.0;
	list->next = NULL;
	return (list);
}

void
	splist_add_front(t_splist **list, t_splist *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}

static t_splist
	*splist_merge(t_splist *list1, t_splist *list2)
{
	t_splist	tmp;
	t_splist	*p;

	ft_bzero(&tmp, sizeof(t_splist));
	p = &tmp;
	while (list1 && list2)
	{
		if (list1->distance <= list2->distance)
		{
			p->next = list2;
			p = list2;
			list2 = list2->next;
		}
		else
		{
			p->next = list1;
			p = list1;
			list1 = list1->next;
		}
	}
	if (!list1)
		p->next = list2;
	else
		p->next = list1;
	return (tmp.next);
}

t_splist
	*splist_sort(t_splist *head)
{
	t_splist	*partition;
	t_splist	*prev;
	t_splist	*back;

	if (!head || !head->next)
		return (head);
	prev = head;
	back = head->next;
	if (back)
		back = back->next;
	while (back && back->next)
	{
		prev = prev->next;
		back = back->next->next;
	}
	partition = prev->next;
	prev->next = NULL;
	return (splist_merge(splist_sort(head), splist_sort(partition)));
}

void
	splist_clear(t_splist **list)
{
	t_splist	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		tmp = NULL;
	}
}
