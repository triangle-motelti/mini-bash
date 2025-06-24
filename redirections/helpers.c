/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:29:34 by motelti           #+#    #+#             */
/*   Updated: 2025/06/24 10:52:16 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	signal_setup(struct sigaction sa_heredoc, struct sigaction sa_old)
{
	sigemptyset(&sa_heredoc.sa_mask);
	sigaction(SIGINT, &sa_heredoc, &sa_old);
}

void	*ctrld_heredoc(char *buf, struct sigaction sa_old)
{
	buf = malloc(1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	sigaction(SIGINT, &sa_old, NULL);
	return (buf);
}

void	*eof_heredoc(char *buf)
{
	buf = malloc(1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	return (buf);
}
