/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:48:11 by motelti           #+#    #+#             */
/*   Updated: 2025/05/24 12:20:41 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int		is_builtin(char *cmd);

void	echo(int ac, char **av);
// int		cd(int ac, char **args);
int     cd(t_shell *shell, int ac, char **args);
void	pwd(int ac);
void	ft_exit(int ac, char **args);
void	ft_env(t_shell *mini, int ac, char **av);


void	ft_export(t_shell *mini, int ac, char **av);
void	export_ac(t_shell *shell, char **arr, int i);
t_env	*find_env_node(t_env *env, const char *key);
int		update_env_node(t_env *node, char *value);
void	sort_env(char **env_arr);

void	unset(t_shell *mini, int ac, char **args);

int		append_env_node(t_shell *mini, char *key, char *value);

#endif