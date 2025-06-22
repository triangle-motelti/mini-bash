//===> header <===

#include "redirection.h"

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
