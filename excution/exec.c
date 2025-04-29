/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:55:19 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 10:21:13 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void	path_check(t_shell *mini, char **envp, char **args)
{
	// ft_putstr_fd("minishell: ", STDERR_FILENO);
	// ft_putstr_fd(args[0], STDERR_FILENO);
	// ft_putstr_fd(": command not found\n", STDERR_FILENO);
	// mini->exit_status = 127;
	// free_split(envp);
	// return ;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	if (ft_strchr(args[0], '/'))
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	// mini->exit_status = 127;
	free_split(envp);
	// if (envp)
	// 	free_split(envp);
	exit(127);
	return ;
}

void	fork_check1(char *path, t_shell *mini, char **envp)
{
	perror("minishell: fork");
	free(path);
	free_split(envp);
	mini->exit_status = 1;
	return ;
}

void	fork_check2(char *path, char **args, char **envp)
{
	execve(path, args, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == 13)
		ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(path);
	free_split(envp);
	exit(126);
}

void	execute_external(t_shell *mini, char **args)
{
	pid_t	pid;
	int		status;
	char	**envp;
	char	*path;

	envp = copy_env_list(mini, mini->env);
	path = path_cmd(args[0], envp);
	if (!path)
		path_check(mini, envp, args);
	pid = fork();
	if (pid == -1)
		fork_check1(path, mini, envp);
	else if (pid == 0)
		fork_check2(path, args, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->exit_status = 128 + WTERMSIG(status);
	}
	free(path);
	free_split(envp);
}
