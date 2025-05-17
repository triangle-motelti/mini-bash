/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:28:33 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/17 12:44:18 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(void *content, int type)
{
	t_token	*aloc;

	aloc = (t_token *)malloc(sizeof(t_token));
	if (!aloc)
		return (NULL);
	aloc->value = content;
	aloc->quote = -1;
	aloc->ambiguous = 0;
	aloc->prev = NULL;
	aloc->flag = type;
	aloc->next = NULL;
	return (aloc);
}
