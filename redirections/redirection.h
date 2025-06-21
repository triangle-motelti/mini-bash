/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:46:03 by motelti           #+#    #+#             */
/*   Updated: 2025/06/21 21:55:35 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../minishell.h"

char	*collect_heredoc_input(const char *delimiter);
void	preprocess_heredocs(t_shell *shell, t_command *cmds);
void	setup_redirections(t_redir *redirs);

t_bool	check_ambiguous_redirect(t_shell *mini);

#endif
