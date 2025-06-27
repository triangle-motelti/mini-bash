/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:28:23 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/27 15:24:05 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	handle_fork_error(void)
{
	perror("minishell: fork");
	exit(1);
}

void	handl_herdc(char *input, int pipe_fd[2], t_redir *redir, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		fork_suces(input, pipe_fd, redir, shell);
	else if (pid > 0)
	{
		fork_fails(pid, pipe_fd, redir, shell);
		if (shell->exit_status == 130)
			return ;
	}
	else
		handle_fork_error();
}

void	prces_herdc(t_shell *shell, int pipe_fd[2], t_redir *redir, char *input)
{
	if (pipe(pipe_fd) < 0)
	{
		perror("minishell");
		exit(1);
	}
	handl_herdc(input, pipe_fd, redir, shell);
}

void	herdoc_chck(t_shell *shell, int pipe_fd[2], t_redir *redir, char *input)
{
	while (redir)
	{
		if (redir->flag == HEREDOC)
		{
			prces_herdc(shell, pipe_fd, redir, input);
			if (shell->exit_status == 130)
				return ;
		}
		redir = redir->next;
	}
}

void	preprocess_heredocs(t_shell *shell, t_command *cmds)
{
	t_command	*cmd;
	t_redir		*redir;
	int			pipe_fd[2];
	char		*input;

	(void)shell;
	cmd = cmds;
	input = NULL;
	redir = NULL;
	while (cmd)
	{
		redir = cmd->redirs;
		herdoc_chck(shell, pipe_fd, redir, input);
		if (shell->exit_status == 130)
			return ;
		cmd = cmd->next;
	}
}
