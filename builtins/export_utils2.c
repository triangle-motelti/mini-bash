/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:59:16 by motelti           #+#    #+#             */
/*   Updated: 2025/06/26 23:58:09 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	extract_key_value(char *arg, t_kv *kv)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return handle_with_equal_sign(arg, eq, kv);
	else
		return without_equal_sign(arg, kv);
}

int	update_append_env(t_shell *mini, char *key, char *value, int is_append)
{
	t_env	*found;

	found = find_env_node(mini->env, key);
	if (is_append)
		return (handle_append_case(mini, found, key, value));
	else
		return (non_append_case(mini, found, key, value));
}
