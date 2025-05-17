/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:28:23 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/17 16:36:25 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	heredoc_check(t_shell *shell, int pipe_fd[2], t_redir *redir, char *input)
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
			redir->heredoc_fd = pipe_fd[0];
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
