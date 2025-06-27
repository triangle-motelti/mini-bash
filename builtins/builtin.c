/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:11:14 by motelti           #+#    #+#             */
/*   Updated: 2025/06/27 14:49:47 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->flag == WORD && current->quote == NQUOTE
			&& current->value[0] == '\0')
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				*tokens = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->value);
			free(current->valuebex);
			free(current);
		}
		current = next;
	}
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0);
}
