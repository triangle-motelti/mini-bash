/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:00:06 by motelti           #+#    #+#             */
/*   Updated: 2025/05/29 15:16:53 by motelti          ###   ########.fr       */
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

void	execute_single_command(t_shell *shell, t_command *cmd)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa_ignore;
	struct sigaction	sa_original;
	int					sig;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, &sa_original);
	preprocess_heredocs(shell, cmd);
	if (is_simple_builtin(shell, cmd))
	{
		setup_redirections(cmd->redirs);
		exec_builtin(shell, cmd->args);
		sigaction(SIGINT, &sa_original, NULL);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		sigaction(SIGINT, &sa_original, NULL);
		return ;
	}
	if (pid == 0)
		exec_child(shell, cmd);
	else
	{
		waitpid(pid, &status, 0);
		sigaction(SIGINT, &sa_original, NULL);
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
}
