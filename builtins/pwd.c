/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:44:04 by motelti           #+#    #+#             */
/*   Updated: 2025/06/16 18:30:58 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(t_shell *shell, int ac)
{
	char	*cwd;
	t_env	*pwd_node;

	(void)ac;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd_node = find_env_node(shell->env, "PWD");
		if (pwd_node && pwd_node->value)
		{
			ft_putstr_fd(pwd_node->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			return ;
		}
		perror("pwd");
		return ;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
}
