/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:18:53 by motelti           #+#    #+#             */
/*   Updated: 2025/05/03 19:03:05 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	exec_pipeline_child(t_shell *shell, t_command *cmd, t_pipeline_info *info, int idx)
{
	if (idx > 0)
		dup2(info->pipes[idx - 1][0], STDIN_FILENO);
	if (idx < info->count - 1)
		dup2(info->pipes[idx][1], STDOUT_FILENO);
	close_pipes(info);
	exec_child(shell, cmd);
}

static int	fork_pipeline(t_shell *shell, t_command *cmds, t_pipeline_info *info)
{
	int			i;
	t_command	*cur;

	cur = cmds;
	i = 0;
	while (i < info->count && cur)
	{
		info->pids[i] = fork();
		if (info->pids[i] < 0)
			perror("fork");
		else if (info->pids[i] == 0)
			exec_pipeline_child(shell, cur, info, i);
		cur = cur->next;
		i++;
	}
	return (i);
}

static void	wait_pipeline(t_shell *shell, t_pipeline_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->count)
	{
		waitpid(info->pids[i], &status, 0);
		if (i == info->count - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			// else if (WIFSIGNALED(status))
			// 	shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	execute_pipeline(t_shell *shell, t_command *cmds)
{
	t_pipeline_info	info;
	int				count;

	count = count_cmds(cmds);
	if (count < 1)
		return ;
	init_pipeline_info(&info, count);
	if (open_pipes(&info))
		return ;
	fork_pipeline(shell, cmds, &info);
	close_pipes(&info);
	wait_pipeline(shell, &info);
}
