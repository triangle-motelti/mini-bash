/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:45:38 by motelti           #+#    #+#             */
/*   Updated: 2025/06/18 19:18:35 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	heredoc_flag(t_redir *redirs, t_shell *shell)
{
	if (redirs->heredoc_fd == -1)
	{
		shell->exit_status = 1;
		return ;
	}
	dup2(redirs->heredoc_fd, STDIN_FILENO);
	close(redirs->heredoc_fd);
}

static void	input_flag(t_redir *redirs, t_shell *shell)
{
	int	fd;

	fd = open(redirs->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		shell->exit_status = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	trunc_flag(t_redir *redirs, t_shell *shell)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		shell->exit_status = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	append_flag(t_redir *redirs, t_shell *shell)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		shell->exit_status = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	setup_redirections(t_redir *redirs, t_shell *shell)
{
	while (redirs)
	{
		if (redirs->flag == INPUT)
			input_flag(redirs, shell);
		else if (redirs->flag == HEREDOC)
			heredoc_flag(redirs, shell);
		else if (redirs->flag == TRUNC)
			trunc_flag(redirs, shell);
		else if (redirs->flag == APPEND)
			append_flag(redirs, shell);
		redirs = redirs->next;
	}
}
