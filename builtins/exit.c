/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:02:46 by motelti           #+#    #+#             */
/*   Updated: 2025/06/13 19:14:16 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	exit_number(char **args, int status)
{
	if (ft_isnumber(args[1]))
	{
		status = ft_atoi(args[1]);
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
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

static void	exit_cases(int ac, char **args, int status, t_shell *shell)
{
	if (ac == 1)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (ac > 2)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
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
