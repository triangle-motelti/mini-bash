/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:01:49 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/18 00:08:50 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*f_clear(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*list;
	void	*cont;

	if (!lst || !del || !f)
		return (NULL);
	list = NULL;
	while (lst)
	{
		cont = f(lst->content);
		if (!cont)
			return (f_clear(list, del));
		new = ft_lstnew(cont);
		if (!new)
		{
			del(cont);
			return (f_clear(list, del));
		}
		ft_lstadd_back(&list, new);
		lst = lst->next;
	}
	return (list);
}
