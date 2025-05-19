/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:40:27 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/19 10:27:31 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// void	free_tokens(t_token *tokens)
// {
// 	t_token	*node;

// 	while (tokens)
// 	{
// 		node = tokens->next;
// 		free(tokens->value);
// 		free(tokens);
// 		tokens = node;
// 	}
// 	// free(tokens);
// }

// void	free_cmds(t_command *cmds)
// {
// 	t_command	*cmd;

// 	while (cmds)
// 	{
// 		cmd = cmds->next;
// 		// free_tokens(cmds->tokens);
// 		free(cmds);
// 		cmds = cmd;
// 	}
// }

void	freeing_array(char **fr)
{
	// int	i;

	// i = 0;
	if (!fr)
		return ;
	// while (fr[i])
	// {
	// 	free(fr[i]);
	// 	i++;
	// }
	free(fr);
	// fr = NULL;
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