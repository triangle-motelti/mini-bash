/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:00:06 by motelti           #+#    #+#             */
/*   Updated: 2025/05/05 17:42:56 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_simple_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0])
		&& cmd->redirs == NULL)
		return (1);
	return (0);
}

static void	exec_builtin_parent(t_shell *shell, char **args)
{
	exec_builtin(shell, args);
}

void	exec_child(t_shell *shell, t_command *cmd)
{
	char	**envp;
	char	*path;

	setup_redirections(cmd->redirs);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		exec_builtin(shell, cmd->args);
		exit(shell->exit_status);
	}
	if (cmd->args && cmd->args[0])
	{
		envp = copy_env_list(shell, shell->env);
		path = path_cmd(cmd->args[0], envp);
		if (!path)
		{
			path_check(shell, envp, &cmd->args[0]);
			free_args(envp);
			exit(127);
		}
		path_execv(cmd, envp, path);
	}
	exit(0);
}

void	execute_single_command(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	preprocess_heredocs(shell, cmd);
	if (is_simple_builtin(shell, cmd))
	{
		setup_redirections(cmd->redirs);
		exec_builtin_parent(shell, cmd->args);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		return ;
	}
	if (pid == 0)
		exec_child(shell, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	// else if (WIFSIGNALED(status))
	//     shell->exit_status = 128 + WTERMSIG(status);
}
