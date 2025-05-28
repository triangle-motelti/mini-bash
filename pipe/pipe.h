/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:17:38 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 14:34:51 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../minishell.h"

typedef struct s_pipeline_info
{
	int		pipes[1024][2];
	pid_t	pids[1024];
	int		count;
}				t_pipeline_info;

//utlis
int		count_cmds(t_command *cmd);
void	init_pipeline_info(t_pipeline_info *info, int count);
int		open_pipes(t_pipeline_info *info);
void	close_pipes(t_pipeline_info *info);

void	execute_pipeline(t_shell *shell, t_command *cmds);

#endif
