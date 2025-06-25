/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:02:46 by motelti           #+#    #+#             */
/*   Updated: 2025/06/25 19:01:18 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	exit_number(char **args, long status)
{
	if (ft_isnumber(args[1]))
	{
		if (ft_atol(args[1], &status))
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		exit(status);
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
}

void	multiple_arguments(int ac, char **args, long status, t_shell *shell)
{
	if (!ft_isnumber(args[1]) || ft_atol(args[1], &status))
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (ac > 2)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return ;
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(status);
}

static void	exit_cases(int ac, char **args, long status, t_shell *shell)
{
	if (ac == 1)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (ac > 2)
	{
		multiple_arguments(ac, args, status, shell);
		return ;
	}
	exit_number(args, status);
}

void	ft_exit(int ac, char **args, t_shell *shell)
{
	int	status;

	status = 0;
	exit_cases(ac, args, status, shell);
}
