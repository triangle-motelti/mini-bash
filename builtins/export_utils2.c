/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:59:16 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 11:08:58 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	extract_key_value(char *arg, char **key, char **value, int *is_append)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (handle_with_equal_sign(arg, eq, key, value, is_append));
	else
		return (without_equal_sign(arg, key, value, is_append));
}

int	update_or_append_env(t_shell *mini, char *key, char *value, int is_append)
{
	t_env	*found;

	found = find_env_node(mini->env, key);
	if (is_append)
		return (handle_append_case(mini, found, key, value));
	else
		return (handle_non_append_case(mini, found, key, value));
}
