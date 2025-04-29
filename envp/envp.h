/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:40:43 by motelti           #+#    #+#             */
/*   Updated: 2025/04/28 11:15:46 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "../minishell.h"

// t_env	*env_node_new(char *value);
// t_env	*build_env_list(char **envp);
t_env	*env_node_new(t_shell *mini, char *env_entry);
t_env	*build_env_list(t_shell *shell, char **envp);
int		env_count(t_env *env);
// char	**copy_env_list(t_env *env);
char	**copy_env_list(t_shell *shell, t_env *env);

#endif