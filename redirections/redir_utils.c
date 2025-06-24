/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:45:10 by motelti           #+#    #+#             */
/*   Updated: 2025/06/24 10:52:48 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static char	*read_heredoc_line(const char *delimiter)
{
	char	*line;

	line = readline("> ");
	if (g_received_signal)
	{
		free(line);
		g_received_signal = 0;
		return (NULL);
	}
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document", 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", 2);
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
		return (free(line), NULL);
	return (line);
}

static char	*grow_buffer(char *old, size_t old_size, size_t add_len)
{
	char	*new;

	new = malloc(old_size + add_len + 2);
	if (!new)
		return (free(old), NULL);
	if (old)
	{
		ft_strcpy(new, old);
		free(old);
	}
	return (new);
}

static char	*append_line(char *buf, size_t *sizep, char *line)
{
	size_t	len;
	char	*nb;

	len = ft_strlen(line);
	nb = grow_buffer(buf, *sizep, len);
	if (!nb)
		return (NULL);
	ft_strcpy(nb + *sizep, line);
	*sizep += len;
	nb[*sizep] = '\n';
	(*sizep)++;
	nb[*sizep] = '\0';
	return (nb);
}

void	init_sigaction(struct sigaction *sa_heredoc, struct sigaction *sa_old)
{
	sa_heredoc->sa_handler = heredoc_sigint_handler;
	sa_heredoc->sa_flags = 0;
	sigemptyset(&sa_heredoc->sa_mask);
	sa_old->sa_handler = NULL;
	sa_old->sa_flags = 0;
	sigemptyset(&sa_old->sa_mask);
}

char	*collect_heredoc_input(const char *delimiter)
{
	char				*buf;
	size_t				buf_size;
	char				*line;
	struct sigaction	sa_heredoc;
	struct sigaction	sa_old;

	buf = NULL;
	buf_size = 0;
	init_sigaction(&sa_heredoc, &sa_old);
	signal_setup(sa_heredoc, sa_old);
	line = read_heredoc_line(delimiter);
	if (!line && !g_received_signal)
		return (ctrld_heredoc(buf, sa_old));
	while (line)
	{
		buf = append_line(buf, &buf_size, line);
		free(line);
		if (!buf)
			return (sigaction(SIGINT, &sa_old, NULL), NULL);
		line = read_heredoc_line(delimiter);
	}
	sigaction(SIGINT, &sa_old, NULL);
	if (!buf && !g_received_signal)
		return (eof_heredoc(buf));
	return (buf);
}
