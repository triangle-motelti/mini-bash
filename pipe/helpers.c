/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:41:24 by motelti           #+#    #+#             */
/*   Updated: 2025/04/22 21:29:18 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	initialize_pipe_info(t_pipe_info *info)
{
	info->is_first = 1;
	info->is_last = 0;
	info->prev_fd = -1;
}

void	free_commands(char **cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return ;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	count_cmds(char **commands)
{
	int	n;

	n = 0;
	while (commands[n])
		n++;
	return (n);
}

int	count_pipes(const char *input)
{
	char	*copy;
	char	*token;
	int		count;

	copy = ft_strdup(input);
	count = 0;
	token = ft_strtok(copy, "|");
	while (token)
	{
		count++;
		token = ft_strtok(NULL, "|");
	}
	free(copy);
	return (count);
}

void	wait_and_update_status(t_shell *shell, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	printf("parent exit status -----------> %d\n", shell->exit_status);
	// else if (WIFSIGNALED(status)) // hady l signals exit status
	// 	shell->exit_status = 128 + WTERMSIG(status);
}
