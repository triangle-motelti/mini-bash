/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:11:49 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 10:54:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_shell *mini, int ac, char **av)
{
	t_env	*current;

	(void)av;
	if (ac > 1)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return ;
	}
	current = mini->env;
	while (current)
	{
		if (ft_strchr(current->value, '='))
			printf("%s\n", current->value);
		current = current->next_pt;
	}
}
