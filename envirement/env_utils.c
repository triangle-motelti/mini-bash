/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:16:04 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 15:18:46 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envirement.h"

char	**copy_env_list1(t_shell *shell, t_env *env)
{
	int		n;
	char	**arr;
	int		i;

	(void)shell;
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

int	fill_env_node(t_env *node, char *env_entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_entry, '=');
	if (equal_sign)
	{
		node->key = ft_strndup(env_entry, equal_sign - env_entry);
		node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		node->key = ft_strdup(env_entry);
		node->value = ft_strdup("");
	}
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		return (0);
	}
	return (1);
}
