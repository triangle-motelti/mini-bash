/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:44:01 by motelti           #+#    #+#             */
/*   Updated: 2025/05/03 18:53:32 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	exec_builtin(t_shell *shell, char **args)
{
	int	ac;
	int	exit_ac;

	ac = 0;
	exit_ac = 1;
	while (args[ac])
		ac++;
	while (args[exit_ac])
		exit_ac++;
	exec_builtins(args, ac, exit_ac, shell);
}

void	exec_builtins(char **args, int ac, int exit_ac, t_shell *mini)
{
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		pwd(ac);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
	{
		if (args[1])
			cd(ac, args);
	}
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		echo(ac, args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(mini, ac, args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
	{
		while (args[exit_ac])
			exit_ac++;
		ft_exit(exit_ac, args);
	}
	else if (ft_strncmp(args[0], "export", 7) == 0)
		ft_export(mini, ac, args);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		unset(mini, ac, args);
}
