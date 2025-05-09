

#ifndef REDIRECTION_H
#define REDIRECTION_H

# include "../minishell.h"

char	*collect_heredoc_input(const char *delimiter);
void	preprocess_heredocs(t_shell *shell, t_command *cmds);
void	setup_redirections(t_redir *redirs);

#endif
