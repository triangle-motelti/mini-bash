/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_sngl_cmd_utlis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:13:23 by motelti           #+#    #+#             */
/*   Updated: 2025/05/23 17:25:33 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	validate_path(const char *path, char *cmd_name)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd_name, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return (126);
		}
		if (access(path, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd_name, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (126);
		}
		return (0);
	}
	return (-1);
}

void	path_execv(t_command *cmd, char **envp, char *path)
{
	int	result;

	if (ft_strcmp(cmd->args[0], "") == 0)
		return ;
	result = validate_path(path, cmd->args[0]);
	if (result != 0)
	{
		free(path);
		free_args(envp);
		if (result == -1)
			exit(127);
		exit(result);
	}
	execve(path, cmd->args, envp);
	perror("execve");
	free(path);
	free_args(envp);
	exit(126);
}

// void	path_execv(t_command *cmd, char **envp, char *path)
// {
// 	execve(path, cmd->args, envp);
// 	perror("execve");
// 	free(path);
// 	free_args(envp);
// 	exit(126);
// }

// void	path_check(t_shell *shell, char **envp, char **args)
// {
// 	t_env	*path_env;

// 	(void)envp;
// 	path_env = find_env_node(shell->env, "PATH");
// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
// 	ft_putstr_fd(args[0], STDERR_FILENO);
// 	if (ft_strchr(args[0], '/') || !path_env)
// 		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
// 	else
// 		ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 	exit(127);
// 	return ;
// }



void	path_check(t_shell *shell, char **envp, char **args)
{
	struct stat	st;
	
	(void)shell;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	if (ft_strchr(args[0], '/'))
	{
		if (stat(args[0], &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
				free_args(envp);
				exit(126);
			}
			if (access(args[0], X_OK) != 0)
			{
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putstr_fd(strerror(errno), STDERR_FILENO);
				ft_putstr_fd("\n", STDERR_FILENO);
				free_args(envp);
				exit(126);
			}
		}
		ft_putstr_fd(": Noo such file or directory\n", STDERR_FILENO);
		free_args(envp);
		exit(127);
	}
	else
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_args(envp);
		exit(127);
	}
}
