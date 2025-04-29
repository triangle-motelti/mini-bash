/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:40:48 by motelti           #+#    #+#             */
/*   Updated: 2025/04/19 14:43:08 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(int ac, char **av)
{
	int	newline;
	int	start;
	int	i;

	newline = 1;
	start = 1;
	if (ac > 1 && ft_strncmp(av[1], "-n", 2) == 0)
	{
		newline = 0;
		start = 2;
	}
	i = start;
	while (i < ac) {
		ft_putstr_fd(av[i], STDOUT_FILENO);
		if (i < ac - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
