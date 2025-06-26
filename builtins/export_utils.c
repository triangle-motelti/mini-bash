/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:40:04 by motelti           #+#    #+#             */
/*   Updated: 2025/06/26 18:34:08 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*find_env_node(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next_pt;
	}
	return (NULL);
}

int	update_env_node(t_env *node, char *value)
{
	char	*newval;

	free(node->value);
	node->value = NULL;
	if (!value)
	{
		node->value = ft_strdup("");
		if (!node->value)
			return (1);
	}
	else
	{
		newval = ft_strdup(value);
		if (!newval)
			return (1);
		node->value = newval;
	}
	return (0);
}


void	sort(char **env_arr, char *tmp, int *i, int *s)
{
	if (ft_strcmp(env_arr[*i], env_arr[*i + 1]) > 0)
	{
		tmp = env_arr[*i];
		env_arr[*i] = env_arr[*i + 1];
		env_arr[*i + 1] = tmp;
		*s = 1;
	}
}

void	export_ac(t_shell *shell, char **arr, int i)
{
	char	*eq;
	size_t	key_len;

	arr = copy_env_list(shell, shell->env);
	if (!arr)
		return ;
	sort_env(arr);
	while (arr[i])
	{
		eq = ft_strchr(arr[i], '=');
		if (eq)
		{
			key_len = eq - arr[i];
			if (*(eq + 1) == '\0')
				printf("declare -x %.*s\n", (int)key_len, arr[i]);
			else
				printf("declare -x %.*s=\"%s\"\n", (int)key_len, arr[i], eq + 1);
		}
		else
			printf("declare -x %s\n", arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	shell->exit_status = 0;
}

void	sort_env(char **env_arr)
{
	int		n;
	int		i;
	int		swapped;
	char	*tmp;

	tmp = NULL;
	n = 0;
	i = 0;
	while (env_arr && env_arr[n])
		n++;
	if (n < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i + 1 < n)
		{
			sort(env_arr, tmp, &i, &swapped);
			i++;
		}
		n--;
	}
}
