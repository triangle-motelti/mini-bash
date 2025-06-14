/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:37:23 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 15:26:34 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIREMENT_H
# define ENVIREMENT_H

# include "../minishell.h"

char	**copy_env_list(t_shell *shell, t_env *env);
t_env	*env_node_new(char *env_entry);
void	copy_env(t_shell *mini, char **envp);

void	set_key_value(char **arr, t_env *env, int i);

int		fill_env_node(t_env *node, char *env_entry);
char	**copy_env_list1(t_shell *shell, t_env *env);
t_env	*build_env_list(t_shell *shell, char **envp);

int		env_count(t_env *env);

#endif
