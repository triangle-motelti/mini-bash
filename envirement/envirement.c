/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:38:41 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 11:58:29 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envirement.h"

static void	no_new_node(t_env *head, t_env *tail)
{
	while (head)
	{
		tail = head->next_pt;
		free(head->key);
		free(head->value);
		free(head);
		head = tail;
	}
}

void	copy_env(t_shell *mini, char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		node = env_node_new(envp[i]);
		if (!node)
		{
			no_new_node(head, tail);
			return ;
		}
		if (!head)
			head = node;
		else
			tail->next_pt = node;
		tail = node;
		i++;
	}
	mini->env = head;
}
