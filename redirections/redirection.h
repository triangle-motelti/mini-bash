/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:46:03 by motelti           #+#    #+#             */
/*   Updated: 2025/06/27 15:39:11 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../minishell.h"

char	*collect_heredoc_input(const char *delimiter);
void	preprocess_heredocs(t_shell *shell, t_command *cmds);
void	setup_redirections(t_redir *redirs);

void	closefd(void);
void	heredoc_sigint_handler(int sig);

void	heredoc_expand(char *input, int pipe_fd[2], char *expanded_input);
void	fork_suces(char *input, int pipe_fd[2], t_redir *redir, t_shell *shell);
void	fork_fails(pid_t pid, int pipe_fd[2], t_redir *redir, t_shell *shell);

void	*ctrld_heredoc(char *buf, struct sigaction sa_old);
void	*eof_heredoc(char *buf);
void	signal_setup(struct sigaction sa_heredoc, struct sigaction sa_old);
void	init_sigaction(struct sigaction *sa_heredoc, struct sigaction *sa_old);
void	ctrlc_check(t_shell *shell, t_redir *redir, int pipe_fd[2]);

#endif
