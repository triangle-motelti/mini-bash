/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:57:00 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 14:21:50 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *value)
{
	char	*val;

	val = (char *)value;
	free(val);
}

static void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*current;
	t_token	*temp;

	if (!*lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		del(temp->value);
		del(temp->valuebex);
		free(temp);
	}
	*lst = NULL;
}

void	clear_tokens(t_token **tokens)
{
	if (!tokens)
		return ;
	ft_lstclear(tokens, del);
}
