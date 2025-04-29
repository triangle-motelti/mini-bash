/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:24:17 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 10:27:21 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

static void	exec_command_child(t_shell *shell, char **args)
{
	char	**envp;
	char	*path;

	envp = copy_env_list(shell, shell->env);
	path = path_cmd(args[0], envp);
	if (!path)
	{
		// ft_putstr_fd("minishell : ", STDERR_FILENO);
		// ft_putstr_fd(args[0], STDERR_FILENO);
		// ft_putstr_fd(": command not found\n", STDERR_FILENO);
		// if (envp)
		// 	free_split(envp);
		// exit(127);
        path_check(shell, envp, args);
	}
	if (execve(path, args, envp) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(args[0]);
		free(path);
		if (envp)
			free_split(envp);
		exit(126);
	}
	printf("exit status -----------> %d\n", shell->exit_status);
}

void	execute_single_command(t_shell *shell, char **args)
{
	pid_t	pid;

	if (is_builtin(args[0]))
	{
		exec_builtin(shell, args);
		printf("builtin exit status -----------> %d\n", shell->exit_status);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		printf("fork fails exit status -----------> %d\n", shell->exit_status);
		return ;
	}
	if (pid == 0)
	exec_command_child(shell, args);
	wait_and_update_status(shell, pid);
}
