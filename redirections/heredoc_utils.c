/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:40:15 by motelti           #+#    #+#             */
/*   Updated: 2025/06/27 15:39:18 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_received_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	closefd();
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(130);
}

void	closefd(void)
{
	int			fd;
	struct stat	st;

	fd = 3;
	while (fd < 1024)
	{
		if (fstat(fd, &st) == 0)
		{
			close(fd);
		}
		fd++;
	}
}

void	heredoc_expand(char *input, int pipe_fd[2], char *expanded_input)
{
	if (expanded_input)
	{
		ft_putstr_fd(expanded_input, pipe_fd[1]);
		free(expanded_input);
	}
	else
		ft_putstr_fd(input, pipe_fd[1]);
}

void	fork_suces(char *input, int pipe_fd[2], t_redir *redir, t_shell *shell)
{
	char	*expanded_input;

	input = collect_heredoc_input(redir->file);
	if (!input)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(130);
	}
	if (redir->expand_var)
	{
		expanded_input = expand_each_token(input, 0, 0, shell);
		heredoc_expand(input, pipe_fd, expanded_input);
	}
	else
		ft_putstr_fd(input, pipe_fd[1]);
	free(input);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(0);
}

void	fork_fails(pid_t pid, int pipe_fd[2], t_redir *redir, t_shell *shell)
{
	int					status;
	struct sigaction	sa_ignore;
	struct sigaction	sa_old;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, &sa_old);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &sa_old, NULL);
	close(pipe_fd[1]);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
		{
			ctrlc_check(shell, redir, pipe_fd);
			return ;
		}
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ctrlc_check(shell, redir, pipe_fd);
		return ;
	}
	redir->heredoc_fd = pipe_fd[0];
}
