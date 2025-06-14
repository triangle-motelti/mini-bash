/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:29:45 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 11:01:26 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_key(const char *key)
{
	int	i;

	if (!key || !*key)
		return (0);
	if (!(isalpha(*key) || *key == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	append_env_node(t_shell *mini, char *key, char *value)
{
	t_env	*new;
	t_env	*cur;

	new = malloc(sizeof(*new));
	if (!new)
		return (1);
	new->key = key;
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	if (!new->key || !new->value)
		return (perror("minishell: malloc"), 1);
	new->next_pt = NULL;
	if (!mini->env)
		mini->env = new;
	else
	{
		cur = mini->env;
		while (cur->next_pt)
			cur = cur->next_pt;
		cur->next_pt = new;
	}
	return (0);
}

int	parse_and_add_variable(t_shell *mini, char *arg)
{
	t_kv	kv;

	if (extract_key_value(arg, &kv))
		return (1);
	if (validate_export_key(arg, kv.key, kv.value, kv.is_append))
		return (1);
	return (update_append_env(mini, kv.key, kv.value, kv.is_append));
}

void	ft_export(t_shell *mini, int ac, char **av)
{
	char	**env_arr;
	int		status;
	int		i;

	env_arr = NULL;
	i = 0;
	if (ac == 1)
		export_ac(mini, env_arr, i);
	else
	{
		status = 0;
		i = 1;
		while (i < ac)
		{
			if (parse_and_add_variable(mini, av[i]) != 0)
				status = 1;
			i++;
		}
		mini->exit_status = status;
	}
}
