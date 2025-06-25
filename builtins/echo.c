/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:40:48 by motelti           #+#    #+#             */
/*   Updated: 2025/06/25 19:17:28 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(int ac, char **av, t_shell *shell)
{
	int	newline;
	int	start;
	int	i;

	newline = 1;
	start = 1;
	i = 1;
	while (i < ac && ft_strcmp(av[i], "-n") == 0)
	{
		newline = 0;
		start++;
		i++;
	}
	i = start;
	while (i < ac)
	{
		ft_putstr_fd(av[i], STDOUT_FILENO);
		if (i < ac - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	shell->exit_status = 0;
}
