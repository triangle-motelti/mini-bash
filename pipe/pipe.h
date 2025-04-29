/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:50:21 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 10:24:48 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../minishell.h"

void	initialize_pipe_info(t_pipe_info *info);
void	setup_redirections(t_pipe_info *info);
void	execute_pipeline(t_shell *shell, char **commands);
char	**split_pipeline(const char *input);
void	free_commands(char **cmds);
int		count_pipes(const char *input);
void	wait_and_update_status(t_shell *shell, pid_t pid);
int		count_cmds(char **commands);

#endif