/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:11:49 by motelti           #+#    #+#             */
/*   Updated: 2025/05/12 08:25:14 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_shell *mini, int ac, char **av)
{
	t_env *current;

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
