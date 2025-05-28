/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:37:23 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 11:59:04 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIREMENT_H
# define ENVIREMENT_H

# include "../minishell.h"

char	**copy_env_list(t_shell *shell, t_env *env);
t_env	*env_node_new(char *env_entry);
void	copy_env(t_shell *mini, char **envp);

void	set_key_value(char **arr, t_env *env, int i);

#endif
