/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:00:06 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 10:24:46 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_simple_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0])
		&& cmd->redirs == NULL)
		return (1);
	return (0);
}

static void	setup_signal_and_heredoc(t_shell *shell, t_command *cmd,
										struct sigaction *sa_ignore,
										struct sigaction *sa_original)
{
	sa_ignore->sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore->sa_mask);
	sa_ignore->sa_flags = 0;
	sigaction(SIGINT, sa_ignore, sa_original);
	preprocess_heredocs(shell, cmd);
}

static void	handle_fork_failure(t_shell *shell, struct sigaction *sa_original)
{
	perror("minishell: fork");
	shell->exit_status = 1;
	sigaction(SIGINT, sa_original, NULL);
}

static void	handle_parent_process(t_shell *shell, pid_t pid,
									struct sigaction *sa_original)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	sigaction(SIGINT, sa_original, NULL);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		shell->exit_status = 128 + sig;
	}
}

void	execute_single_command(t_shell *shell, t_command *cmd)
{
	pid_t				pid;
	struct sigaction	sa_ignore;
	struct sigaction	sa_original;

	setup_signal_and_heredoc(shell, cmd, &sa_ignore, &sa_original);
	if (is_simple_builtin(shell, cmd))
	{
		setup_redirections(cmd->redirs);
		exec_builtin(shell, cmd->args);
		sigaction(SIGINT, &sa_original, NULL);
		return ;
	}
	pid = fork();
	if (pid < 0)
		handle_fork_failure(shell, &sa_original);
	else if (pid == 0)
		exec_child(shell, cmd);
	else
		handle_parent_process(shell, pid, &sa_original);
}
