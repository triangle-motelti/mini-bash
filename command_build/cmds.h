/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by motelti           #+#    #+#             */
/*   Updated: 2025/05/26 14:36:59 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
#define CMDS_H

#include "../minishell.h"

typedef struct	s_build_info
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
// t_command	*build_commands(t_token *tokens);
t_command *build_commands(t_token *tokens, t_shell *shell);

#endif
