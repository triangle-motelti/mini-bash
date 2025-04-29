/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:44:04 by motelti           #+#    #+#             */
/*   Updated: 2025/04/20 20:34:22 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// void	pwd(int ac)
// {
// 	char *cwd;
// 	if (ac > 0)
// 	{
// 		ft_putstr_fd("pwd: too many arguments\n", 2);
// 		return ;
// 	}
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		perror("pwd");
// 		return ;
// 	}
// 	ft_putstr_fd(cwd, 1);
// 	ft_putstr_fd("\n", 1);
// 	free(cwd);
// }

void	pwd(int ac)
{
	char	*cwd;

	// if (ac > 1)
	// {
	// 	ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
	// 	return;
	// }
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return ;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
}