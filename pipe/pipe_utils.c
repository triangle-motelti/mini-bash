/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:28:09 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 10:23:44 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	setup_redirections(t_pipe_info *info)
{
	if (!info->is_first)
	{
		dup2(info->prev_fd, STDIN_FILENO);
		close(info->prev_fd);
	}
	if (!info->is_last)
	{
		close(info->cur_fd[0]);
		dup2(info->cur_fd[1], STDOUT_FILENO);
		close(info->cur_fd[1]);
	}
}

static char	**allocate_and_fill(const char *input, int count)
{
	char	**cmds;
	char	*copy;
	char	*token;
	int		i;

	cmds = malloc((count + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	copy = ft_strdup(input);
	token = ft_strtok(copy, "|");
	i = 0;
	while (token)
	{
		cmds[i] = ft_strtrim(token, " ");
		if (!cmds[i])
			return (free_commands(cmds), free(copy), NULL);
		token = ft_strtok(NULL, "|");
		i++;
	}
	cmds[i] = NULL;
	free(copy);
	return (cmds);
}

char	**split_pipeline(const char *input)
{
	int		count;

	count = count_pipes(input);
	return (allocate_and_fill(input, count));
}
