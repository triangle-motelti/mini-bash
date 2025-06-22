/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:45:38 by motelti           #+#    #+#             */
/*   Updated: 2025/06/22 22:56:20 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	heredoc_flag(t_redir *redirs)
{
	if (redirs->heredoc_fd == -1)
		exit(130);
	dup2(redirs->heredoc_fd, STDIN_FILENO);
	close(redirs->heredoc_fd);
}

static void	input_flag(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	trunc_flag(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	append_flag(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	setup_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->flag == INPUT)
			input_flag(redirs);
		else if (redirs->flag == HEREDOC)
			heredoc_flag(redirs);
		else if (redirs->flag == TRUNC)
			trunc_flag(redirs);
		else if (redirs->flag == APPEND)
			append_flag(redirs);
		redirs = redirs->next;
	}
}
