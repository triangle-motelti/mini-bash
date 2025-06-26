/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:40:48 by motelti           #+#    #+#             */
/*   Updated: 2025/06/26 14:00:32 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	parse_options(int ac, char **av, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] == 'n')
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] == '\0')
		{
			*newline = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	echo(int ac, char **av, t_shell *shell)
{
	int	newline;
	int	start;
	int	i;

	start = parse_options(ac, av, &newline);
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
