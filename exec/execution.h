/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:28:09 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 12:16:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

void	exec_builtin(t_shell *shell, char **args);
void	exec_builtins(char **args, int ac, int exit_ac, t_shell *mini);

void	exec_child(t_shell *shell, t_command *cmd);

char	*path_cmd(char *cmd, char *const *envp);

void	path_check(t_shell *shell, char **envp, char **args);
void	path_execv(t_command *cmd, char **envp, char *path);
void	execute_single_command(t_shell *shell, t_command *cmd);

#endif
