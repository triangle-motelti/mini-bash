/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:59:07 by motelti           #+#    #+#             */
/*   Updated: 2025/05/03 17:59:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	count_cmds(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	set_pipe_status(t_shell *shell, int status)
{
	int	sig;

	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		shell->exit_status = 128 + sig;
	}
}

void	init_pipeline_info(t_pipeline_info *info, int count)
{
	info->count = count;
}

int	open_pipes(t_pipeline_info *info)
{
	int	i;

	i = 0;
	while (i < info->count - 1)
	{
		if (pipe(info->pipes[i]) < 0)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

void	close_pipes(t_pipeline_info *info)
{
	int	i;

	i = 0;
	while (i < info->count - 1)
	{
		close(info->pipes[i][0]);
		close(info->pipes[i][1]);
		i++;
	}
}
