/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:45:38 by motelti           #+#    #+#             */
/*   Updated: 2025/05/02 13:47:32 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	setup_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->flag == INPUT)
		{
			int fd = open(redirs->file, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->flag == TRUNC)
		{
			int fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->flag == APPEND)
		{
			int fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
}
