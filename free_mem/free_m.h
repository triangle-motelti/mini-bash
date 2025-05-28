/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_m.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:22:27 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 12:18:10 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_M_H
# define FREE_M_H

# include "../minishell.h"

void	free_args(char **args);
void	free_redirs(t_redir *redirs);
void	free_commands(t_command *cmds);
void	free_tokens(t_token *tokens);

#endif
