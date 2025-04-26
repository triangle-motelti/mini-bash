/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:40:27 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/26 09:44:13 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tokens(t_token *tokens)
{
	t_token	*node;

	while (tokens->next)
	{
		node = tokens->next;
		free(tokens->value);
		free(tokens->next);
		tokens = node;
	}
	free(tokens);
}

void    free_env(t_env *env)
{
	t_env	*next;

	while (env->next_pt)
	{
		next = env->next_pt;
		free(env->value);
		free(env->next_pt);
		env = next;
	}
	// free(tokens);
}