/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:03:43 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 14:05:53 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	remove_env_node(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;

	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next_pt = current->next_pt;
			else
				*env = current->next_pt;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next_pt;
	}
}

void	unset(t_shell *mini, int ac, char **args)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		remove_env_node(&mini->env, args[i]);
		i++;
	}
	mini->exit_status = 0;
}
