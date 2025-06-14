/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 11:30:47 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "../minishell.h"

typedef struct s_build_info
{
	t_command	*list;
	t_command	*cmd;
	t_redir		*last_redir;
	char		**args;
	int			arg_count;
	t_token		*tok;
}				t_build_info;

t_command	*create_command(void);
int			finalize_args(t_command *cmd, char **args, int count);
int			add_arg(char ***args, int *count, char *value);
int			handl_word(t_token *tok, char ***args, int *count);
int			init_build(t_token *tokens, t_build_info *info);
t_command	*finish_build(t_build_info *info);
t_command	*build_commands(t_token *tokens, t_shell *shell);

int			add_redir(t_command *cmd, t_redir **last, int flag, char *file);
int			add_redirc(t_command *cmd, t_redir **last, int flag, char *delim);
void		set_heredoc_expand(t_redir *last, int flag, int expand_vars);

char		*process_quoted_delimiter(char *delimiter);

#endif
