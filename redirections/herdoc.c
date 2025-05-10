/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 07:46:06 by kali              #+#    #+#             */
/*   Updated: 2025/05/10 17:56:16 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	heredoc_check(int pipe_fd[2], t_redir *redir, char *input)
{
	while (redir)
	{
		if (redir->flag == HEREDOC)
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("minishell");
				exit(1);
			}
			input = collect_heredoc_input(redir->file);
			if (!input)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				redir->heredoc_fd = -1;
				return ;
			}
			ft_putstr_fd(input, pipe_fd[1]);
			close(pipe_fd[1]);
			redir->heredoc_fd = pipe_fd[0];
			free(input);
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

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		heredoc_check(pipe_fd, redir, input);
		cmd = cmd->next;
	}
}
