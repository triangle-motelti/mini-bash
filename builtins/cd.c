/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:03 by motelti           #+#    #+#             */
/*   Updated: 2025/04/17 16:25:39 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd(int ac, char **args)
{
	if (ac != 2)
	{
		ft_putstr_fd("cd: usage: with only a relative or absolute path\n", 2);
		return (-1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}
