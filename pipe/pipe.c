/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:18:53 by motelti           #+#    #+#             */
/*   Updated: 2025/06/19 21:05:35 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	exec_pipe_setup(t_command *cmd,
							t_pipeline_info *info, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i > 0)
		dup2(info->pipes[i - 1][0], STDIN_FILENO);
	if (i < info->count - 1)
		dup2(info->pipes[i][1], STDOUT_FILENO);
	close_pipes(info);
	setup_redirections(cmd->redirs);
}

void	exec_pipe(t_shell *shell, t_command *cmd, t_pipeline_info *info, int i)
{
	exec_pipe_setup(cmd, info, i);
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->redirs)
			exit(shell->exit_status);
		exit(0);
	}
	exec_child(shell, cmd);
}

int	fork_pipeline(t_shell *shell, t_command *cmds, t_pipeline_info *info)
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
			exec_pipe(shell, cur, info, i);
		cur = cur->next;
		i++;
	}
	return (i);
}

static void	wait_pipeline(t_shell *shell, t_pipeline_info *info)
{
	int	i;
	int	status;
	int	interrupted;

	i = 0;
	interrupted = 0;
	while (i < info->count)
	{
		waitpid(info->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			interrupted = 1;
		if (i == info->count - 1)
			set_pipe_status(shell, status);
		i++;
	}
	if (interrupted)
		write(STDOUT_FILENO, "\n", 1);
}

void	execute_pipeline(t_shell *shell, t_command *cmds)
{
	t_pipeline_info		info;
	int					count;
	struct sigaction	sa_ignore;
	struct sigaction	sa_oldint;
	struct sigaction	sa_oldquit;

	count = count_cmds(cmds);
	if (count < 1)
		return ;
	preprocess_heredocs(shell, cmds);
	init_pipeline_info(&info, count);
	if (open_pipes(&info))
		return ;
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, &sa_oldint);
	sigaction(SIGQUIT, &sa_ignore, &sa_oldquit);
	fork_pipeline(shell, cmds, &info);
	close_pipes(&info);
	wait_pipeline(shell, &info);
	sigaction(SIGINT, &sa_oldint, NULL);
	sigaction(SIGQUIT, &sa_oldquit, NULL);
}
