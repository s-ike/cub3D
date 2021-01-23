/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 00:41:31 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/08 17:02:19 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_head;

	if (!lst || !f || !del)
		return (NULL);
	if (!(new = ft_lstnew(f(lst->content))))
		return (NULL);
	new_head = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (new_head);
}
