/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:32:07 by motelti           #+#    #+#             */
/*   Updated: 2025/04/27 22:44:13 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	execute_command(t_shell *mini, char *cmd)
{
	char	**args;
	char	**envp;
	char	*path;

	args = parse_input(mini, cmd);
	if (!args || !args[0])
		exit(1);
	if (is_builtin(args[0]))
	{
		exec_builtin(mini, args);
		exit(mini->exit_status);
	}
	envp = copy_env_list(mini, mini->env);
	path = path_cmd(args[0], envp);
	if (!path)
	{
		path_check(mini, envp, args);
		exit(127);
	}
	execve(path, args, envp);
	free(path);
	free_split(envp);
	exit(126);
}

static void	child_executor(t_shell *mini, char *cmd, t_pipe_info *info)
{
	setup_redirections(info);
	execute_command(mini, cmd);
}

static void	parent_executor(t_pipe_info *info)
{
	if (info->is_first == 0 && info->prev_fd >= 0)
		close(info->prev_fd);
	if (info->is_last == 0)
	{
		close(info->cur_fd[1]);
		info->prev_fd = info->cur_fd[0];
	}
	else
		info->prev_fd = -1;
}

void	create_child(t_shell *mini, char **commands, int i, t_pipe_info *info)
{
	pid_t	pid;

	info->is_first = (i == 0);
	info->is_last = (commands[i + 1] == NULL);
	if (!info->is_last)
	{
		if (pipe(info->cur_fd) < 0)
		{
			perror("minishell: pipe");
			exit(1);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		exit(1);
	}
	if (pid == 0)
		child_executor(mini, commands[i], info);
	parent_executor(info);
}

void	execute_pipeline(t_shell *mini, char **commands)
{
	int			i;
	t_pipe_info	info;

	initialize_pipe_info(&info);
	i = 0;
	while (commands[i])
	{
		create_child(mini, commands, i, &info);
		i++;
	}
	while (wait(NULL) > 0)
		;
}
