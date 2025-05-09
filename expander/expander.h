/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/09 10:24:06 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H
#include "../minishell.h"

t_bool	expander(t_shell *mini);
// void	copy_env(t_shell *mini, char **env, int i);
char	*get_env_value(char *value, t_shell *mini);

t_env	*build_env_list(t_shell *shell, char **envp);
t_bool	is_limiter_expanders(char *value, int i);


#endif