/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:38:41 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 15:24:42 by motelti          ###   ########.fr       */
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

static t_env	*env_node_new1(t_shell *mini, char *env_entry)
{
	t_env	*node;

	if (!env_entry)
		return (NULL);
	(void)mini;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (!fill_env_node(node, env_entry))
		return (free(node), NULL);
	node->next_pt = NULL;
	return (node);
}

static int	append_env_node2(t_env **head, t_env **tail, t_env *node)
{
	if (!node)
		return (0);
	if (!*head)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next_pt = node;
		*tail = node;
	}
	return (1);
}

t_env	*build_env_list(t_shell *shell, char **envp)
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
		node = env_node_new1(shell, envp[i]);
		if (!append_env_node2(&head, &tail, node))
			return (NULL);
		i++;
	}
	return (head);
}
