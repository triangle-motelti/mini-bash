/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:57:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/01 20:01:22 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_bool	expander(t_shell *mini)
{
	t_token	*token;
	int		i;

	token = mini->tokens;
	while (token)
	{
		i = 0;
		// if (!errors())
			// return (FALSE);//here i'm gonna handle the syntax when there is a dolar sign
		// select_var(mini);
		// while (token->value[i])//loop on each character on the value element of each node
		// {
		// 	if (token->value[i] == '$')
		// 	{
		// 		//here i will track the next and the prev of the dollar sign for syntax errors;
		// 		if (is_separator(token->value, i + 1) || is_wspace(token->value[i + 1]))
		// 			return (FALSE);
		// 	}
		// 	if (token->value[0] == '\'' && token->value[i] == '$')//if 
		// 		return (FALSE);//for every false return value i print the string as it is.
		// 	i++;
		// }
		
		token = token->next;
	}
	return (TRUE);
}
