/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:45:10 by motelti           #+#    #+#             */
/*   Updated: 2025/05/27 10:38:52 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

t_bool	check_ambiguous_redirect(t_shell *mini)
{
	t_token	*token;
	t_token	*next;

	token = mini->tokens;
	while (token)
	{
		if (token->flag == TRUNC || token->flag == APPEND || token->flag == INPUT)
		{
			next = token->next;
			if (next && next->ambiguous == 1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				if (next->valuebex)
					ft_putstr_fd(next->valuebex, STDERR_FILENO);
				else
					ft_putstr_fd("(null)", STDERR_FILENO);
				ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
				mini->exit_status = 1;
				return (TRUE);
			}
		}
		token = token->next;
	}
	return (FALSE);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;

	g_received_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(130);
}

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
		return (NULL);
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

char *collect_heredoc_input(const char *delimiter)
{
	char				*buf;
	size_t				buf_size;
	char				*line;
	struct sigaction	sa_heredoc;
	struct sigaction	sa_old;
	
	buf = NULL;
	buf_size = 0;
	sa_heredoc.sa_handler = heredoc_sigint_handler;
	sa_heredoc.sa_flags = 0;
	sigemptyset(&sa_heredoc.sa_mask);
	sigaction(SIGINT, &sa_heredoc, &sa_old);
	while ((line = read_heredoc_line(delimiter)) != NULL)
	{
		buf = append_line(buf, &buf_size, line);
		free(line);
		if (!buf)
			return (sigaction(SIGINT, &sa_old, NULL), NULL);
	}
	sigaction(SIGINT, &sa_old, NULL);
	return (buf);
}
