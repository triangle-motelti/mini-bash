/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:28:55 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 10:24:55 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCUTION_H
# define EXCUTION_H

#include "../minishell.h"

void	execute_external(t_shell *mini, char **args);
char	**find_path(char *const *envp);
char	*path_cmd(char *cmd, char *const *envp);
void	exec_builtins(char **args, int ac, int exit_ac, t_shell *mini);
void	free_split(char **split);
void	exec_builtin(t_shell *shell, char **args);
void	path_check(t_shell *mini, char **envp, char **args);
void	fork_check1(char *path, t_shell *mini, char **envp);
void	fork_check2(char *path, char **args, char **envp);
void	execute_single_command(t_shell *shell, char **args);

#endif