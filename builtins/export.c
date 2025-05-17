/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:29:45 by motelti           #+#    #+#             */
/*   Updated: 2025/05/12 08:24:57 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_key(const char *key)
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

static int	extract_key_value(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_strndup(arg, eq - arg);
		if (!*key)
			return (1);
		*value = ft_strdup(eq + 1);
		if (!*value)
			return (free(*key), 1);
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (1);
		*value = NULL;
	}
	return (0);
}

static int	append_env_node(t_shell *mini, char *key, char *value)
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
	char	*key;
	char	*value;
	t_env	*found;
	int		ret;

	if (extract_key_value(arg, &key, &value))
		return (1);
	if (!is_valid_key(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (free(key), free(value), 1);
	}
	found = find_env_node(mini->env, key);
	if (found)
		ret = update_env_node(found, value);
	else
		ret = append_env_node(mini, key, value);
	return (free(value), ret);
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
