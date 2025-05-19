/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:28:33 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/19 22:42:30 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_token	*ft_lstnew(void *content, int type)
// {
// 	t_token	*aloc;

// 	aloc = (t_token *)malloc(sizeof(t_token));
// 	if (!aloc)
// 		return (NULL);
// 	aloc->value = content;
// 	aloc->valuebex = ft_strdup(content);
//     if (!aloc->valuebex)
//     {
//         free(aloc);
//         return (NULL);
//     }
// 	aloc->quote = -1;
// 	aloc->ambiguous = 0;
// 	aloc->prev = NULL;
// 	aloc->flag = type;
// 	aloc->next = NULL;
// 	return (aloc);
// }

t_token *ft_lstnew(void *content, int type)
{
    t_token *aloc;

    aloc = (t_token *)malloc(sizeof(t_token));
    if (!aloc)
        return (NULL);
    aloc->value = content;
    aloc->valuebex = ft_strdup((char *)content);
    if (!aloc->valuebex && content)
    {
        free(aloc);
        return (NULL);
    }
    aloc->quote = -1;
    aloc->ambiguous = 0;
    aloc->prev = NULL;
    aloc->flag = type;
    aloc->next = NULL;
    return (aloc);
}
