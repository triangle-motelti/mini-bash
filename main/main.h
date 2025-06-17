/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:06:25 by motelti           #+#    #+#             */
/*   Updated: 2025/06/17 22:32:50 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minishell.h"

int		main(int argc, char **v, char **env);

void	free_env_list(t_env *env);
t_bool	parsing_and_expanding(t_shell *mini);
void	execute_commands(t_shell *shell, t_command *cmds);

void	pwd_env(t_shell *minishell);
void	empty_env(t_shell *minishell);

#endif
