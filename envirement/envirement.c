/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:38:41 by motelti           #+#    #+#             */
/*   Updated: 2025/05/12 08:22:49 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envirement.h"

static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next_pt;
	}
	return (count);
}

char	**copy_env_list(t_shell *shell, t_env *env)
{
	int		n;
	char	**arr;
	int		i;

	(void)shell;
	n = env_count(env);
	arr = malloc((n + 1) * sizeof(char *));
	i = 0;
	if (!arr)
		return (NULL);
	while (env)
	{
		arr[i] = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			return (free(arr), NULL);
		}
		ft_strcpy(arr[i], env->key);
		ft_strcat(arr[i], "=");
		ft_strcat(arr[i], env->value);
		i++;
		env = env->next_pt;
	}
	return (arr[i] = NULL, arr);
}

t_env *env_node_new(char *env_entry)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	char *eq = ft_strchr(env_entry, '=');
	if (eq)
	{
		node->key = ft_strndup(env_entry, eq - env_entry);
		node->value = ft_strdup(eq + 1);
	}
	else
	{
		node->key = ft_strdup(env_entry);
		node->value = ft_strdup("");
	}
	if (!node->key || !node->value)
		return (free(node->key), free(node->value), free(node), NULL);
	return (node->next_pt = NULL, node);
}

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
