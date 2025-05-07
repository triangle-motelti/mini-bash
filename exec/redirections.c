/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:45:38 by motelti           #+#    #+#             */
/*   Updated: 2025/05/05 20:47:31 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	heredoc_flag(t_redir *redirs)
{
	int			fd;
	t_command	*cmd;
	char		*input;
	int			pipe_fd[2];

	input = collect_heredoc_input(redirs->file);
	if (!input)
	{
		ft_putstr_fd("minishell: heredoc failed\n", STDERR_FILENO);
		exit(1);
	}
	if (pipe(pipe_fd) < 0)
	{
		perror("minishell: pipe");
		free(input);
		exit(1);
	}
	write(pipe_fd[1], input, strlen(input));
	close(pipe_fd[1]);
	free(input);
	fd = pipe_fd[0];
	dup2(fd, STDIN_FILENO);
	close(fd);
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
