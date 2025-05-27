/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:28:23 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/27 10:36:50 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	fork_success(char *input, int pipe_fd[2], t_redir *redir, t_shell *shell)
{
	input = collect_heredoc_input(redir->file);
	if (!input)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(130);
	}
	if (redir->expand_var)
	{
		char *expanded_input = expand_each_token(input, 0, 0, shell);
		if (expanded_input)
		{
			ft_putstr_fd(expanded_input, pipe_fd[1]);
			free(expanded_input);
		}
		else
			ft_putstr_fd(input, pipe_fd[1]);
	}
	else
		ft_putstr_fd(input, pipe_fd[1]);
	free(input);
	close(pipe_fd[1]);
	exit(0);
}
	
static void	fork_fails(pid_t pid, int pipe_fd[2], t_redir *redir, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		shell->exit_status = 130;
		redir->heredoc_fd = -1;
		close(pipe_fd[0]);
		return ;
	}
	redir->heredoc_fd = pipe_fd[0];
}

static void	heredoc_check(t_shell *shell, int pipe_fd[2], t_redir *redir, char *input)
{
	pid_t	pid;

	while (redir)
	{
		if (redir->flag == HEREDOC)
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("minishell");
				exit(1);
			}
			pid = fork();
			if (pid == 0)
				fork_success(input, pipe_fd, redir, shell);
			else if (pid > 0) 
				fork_fails(pid, pipe_fd, redir, shell);
			else
			{
				perror("minishell: fork");
				exit(1);
			}
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
		heredoc_check(shell, pipe_fd, redir, input);
		cmd = cmd->next;
	}
}
