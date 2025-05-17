/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:12:21 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/01 09:54:16 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_commands	*new_token_node(t_token *tokens)
{
	t_commands	*new_command;

	new_command = malloc(sizeof(t_commands));
	if (!new_command)
		return (NULL);
	// new_command->tokens = tokens;
	new_command->argument = NULL;
	new_command->redirection = NULL;
	new_command->file = NULL;
	new_command->fd_in = STDIN_FILENO;
	new_command->fd_out = STDOUT_FILENO;
	new_command->next = NULL;
	new_command->command = NULL;
	return (new_command);
}

void	flstadd_command_back(t_commands **lst, t_commands *new)
{
	t_commands	*t;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		t = *lst;
		while (t->next)
			t = t->next;
		t->next = new;	
	}
}
