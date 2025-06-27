/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:56:32 by motelti           #+#    #+#             */
/*   Updated: 2025/06/27 12:44:28 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	handle_with_equal_sign(char *arg, char *eq, t_kv *result)
{
	if (eq > arg && *(eq - 1) == '+')
	{
		result->is_append = 1;
		result->key = ft_strndup(arg, eq - 1 - arg);
	}
	else
	{
		result->is_append = 0;
		result->key = ft_strndup(arg, eq - arg);
	}
	if (!result->key)
		return (1);
	if (*(eq + 1) == '\0')
		result->value = ft_strdup("");
	else
		result->value = ft_strdup(eq + 1);
	if (!result->value)
		return (free(result->key), 1);
	return (0);
}

int	without_equal_sign(char *arg, t_kv *kv)
{
	kv->key = ft_strdup(arg);
	if (!kv->key)
		return (1);
	kv->value = NULL;
	kv->is_append = 0;
	return (0);
}

int	validate_export_key(char *arg, char *key, char *value, int is_append)
{
	if (!is_valid_key(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (free(key), free(value), 1);
	}
	if (is_append && value && value[0] == '\0')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (free(key), free(value), 1);
	}
	return (0);
}

int	handle_append_case(t_shell *mini, t_env *found, char *key, char *value)
{
	char	*new_value;
	int		ret;

	if (found)
	{
		new_value = ft_strjoin(found->value, value);
		if (!new_value)
			return (free(key), free(value), 1);
		ret = update_env_node(found, new_value);
		free(new_value);
		free(key);
	}
	else
		ret = append_env_node(mini, key, value);
	return (free(value), ret);
}

int	non_append_case(t_shell *mini, t_env *found, char *key, char *value)
{
	int	ret;

	if (found)
	{
		if (value != NULL)
		{
			ret = update_env_node(found, value);
			free(value);
		}
		else
			ret = 0;
		free(key);
	}
	else
	{
		ret = append_env_node(mini, key, value);
		free(value);
	}
	return (ret);
}
