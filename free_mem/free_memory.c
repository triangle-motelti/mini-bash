/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:26:53 by motelti           #+#    #+#             */
/*   Updated: 2025/05/26 12:34:13 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_m.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_redirs(t_redir *redirs)
{
	t_redir *next;
	
	while (redirs)
	{
		next = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = next;
	}
}

void	free_commands(t_command *cmds)
{
	t_command	*next;
	
	while (cmds)
	{
		next = cmds->next;
		free_args(cmds->args);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current->valuebex);
		free(current);
		current = next;
	}
}
