/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/02 15:09:54 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H
#include "../minishell.h"

t_bool	expander(t_shell *mini);
// void	copy_env(t_shell *mini, char **env, int i);

t_env	*build_env_list(t_shell *shell, char **envp);


#endif