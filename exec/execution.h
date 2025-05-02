/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:20:53 by motelti           #+#    #+#             */
/*   Updated: 2025/05/02 15:03:39 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "../minishell.h"

void	exec_builtin(t_shell *shell, char **args);
void	exec_builtins(char **args, int ac, int exit_ac, t_shell *mini);

void	exec_child(t_shell *shell, t_command *cmd);

void	setup_redirections(t_redir *redirs);
void	execute_single_command(t_shell *shell, t_command *cmd);
char	*path_cmd(char *cmd, char *const *envp);

#endif
