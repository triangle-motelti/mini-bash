/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:56:16 by motelti           #+#    #+#             */
/*   Updated: 2025/06/27 12:45:47 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envirement.h"

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

void	set_key_value(char **arr, t_env *env, int i)
{
	ft_strcpy(arr[i], env->key);
	if (env->value != NULL)
	{
		ft_strcat(arr[i], "=");
		ft_strcat(arr[i], env->value);
	}
}

char	**copy_env_list(t_shell *shell, t_env *env)
{
	int		n;
	char	**arr;
	int		i;

	(void)shell;
	i = 0;
	n = env_count(env);
	arr = malloc((n + 1) * sizeof(char *));
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
		set_key_value(arr, env, i);
		i++;
		env = env->next_pt;
	}
	return (arr[i] = NULL, arr);
}

t_env	*env_node_new(char *env_entry)
{
	t_env	*node;
	char	*eq;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(env_entry, '=');
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
