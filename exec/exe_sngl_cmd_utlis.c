/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_sngl_cmd_utlis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:13:23 by motelti           #+#    #+#             */
/*   Updated: 2025/05/03 17:13:56 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	path_execv(t_command *cmd, char **envp, char *path)
{
	execve(path, cmd->args, envp);
	perror("execve");
	free(path);
	free_args(envp);
	exit(126);
}

void	path_check(t_shell *shell, char **envp, char **args)
{
	t_env	*path_env;

	path_env = find_env_node(shell->env, "PATH");
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	if (ft_strchr(args[0], '/') || !path_env)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
	return ;
}
