/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:02:46 by motelti           #+#    #+#             */
/*   Updated: 2025/06/25 14:41:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

int	ft_isspace(int c)
{
	if (c == 32)
		return (1);
	return (0);
}

int	ft_atol(const char *p, long *result)
{
	int		i;
	int		sign;
	long	r;

	i = 0;
	sign = 1;
	r = 0;
	while (ft_isspace(p[i]))
		i++;
	if (p[i] == '-')
		sign = -1;
	i += (p[i] == '+' || p[i] == '-');
	if (!ft_isdigit(p[i]))
		return (1);
	while (ft_isdigit(p[i]))
	{
		if (r > LONG_MAX / 10
			|| (r == LONG_MAX / 10 && (p[i] - '0') > LONG_MAX % 10))
			return (1);
		r = r * 10 + (p[i] - '0');
		i++;
	}
	if (p[i] && ft_isascii(p[i]))
		return (1);
	return (*result = r * sign, 0);
}

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
