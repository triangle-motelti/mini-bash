/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:45:10 by motelti           #+#    #+#             */
/*   Updated: 2025/05/23 12:19:07 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

// void	check_ambiguous_redirect(t_shell *mini)
// {
// 	t_token	*token;
// 	t_token	*next;

// 	token = mini->tokens;
// 	while (token)
// 	{
// 		if (token->flag == TRUNC || token->flag == APPEND || token->flag == INPUT)
// 		{
// 			next = token->next;
// 		// 	if (next && next->ambiguous == 1)
// 		// 	{
// 		// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		// 		ft_putstr_fd(next->valuebex, STDERR_FILENO);
// 		// 		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
// 		// 		mini->exit_status = 1;
// 		// 	}
//             if (next && next->ambiguous == 1)
//             {
//                 ft_putstr_fd("minishell: ", STDERR_FILENO);
//                 if (next->valuebex)
//                     ft_putstr_fd(next->valuebex, STDERR_FILENO);
//                 else
//                     ft_putstr_fd("(null)", STDERR_FILENO);
//                 ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
//                 mini->exit_status = 1;
//                 return ;
//             }
// 		}
// 		token = token->next;
// 	}
// 	return ;
// }

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
