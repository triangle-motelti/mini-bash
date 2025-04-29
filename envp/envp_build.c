/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:39:45 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 12:07:10 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

int	env_count(t_env *env)
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

	n = env_count(env);
	arr = malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin_sep(env->key, env->value, "=");
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			return (free(arr), NULL);
		}
		i++;
		env = env->next_pt;
	}
	return (arr[i] = NULL, arr);
}

t_env	*env_node_new(t_shell *mini, char *env_entry)
{
	t_env	*node;
	char	*equal_sign;
    char    *key_part;
    char    *value_part;

	if (!env_entry)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(env_entry, '=');
	if (equal_sign)
	{
		node->key = ft_strndup(env_entry, equal_sign - env_entry);
		node->value = ft_strdup(equal_sign + 1);
		if (!node->key || !node->value)
			return (NULL);
	}
	else
	{
		node->key = ft_strdup(env_entry);
		node->value = ft_strdup("");
		if (!node->key || !node->value)
			return (NULL);
	}
	if (!node->key || !node->value)
		return (free(node->key), free(node->value), free(node), NULL);
	return (node->next_pt = NULL, node);
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
		node = env_node_new(shell, envp[i]);
		if (!node)
			return (NULL);
		if (!head)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next_pt = node;
			tail = node;
		}
		i++;
	}
	return (head);
}
