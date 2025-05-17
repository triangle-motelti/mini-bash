/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:45:10 by motelti           #+#    #+#             */
/*   Updated: 2025/05/17 17:43:12 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static char	*read_heredoc_line(const char *delimiter)
{
	char	*line;

	line = readline("> ");
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

char	*collect_heredoc_input(const char *delimiter)
{
	char	*buf;
	size_t	buf_size;
	char	*line;

	buf = NULL;
	buf_size = 0;
	line = read_heredoc_line(delimiter);
	if (!line)
		return (NULL);
	while (line  != NULL)
	{
		buf = append_line(buf, &buf_size, line);
		free(line);
		if (!buf)
			return (NULL);
		line = read_heredoc_line(delimiter);
	}
	return (buf);
}
