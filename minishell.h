/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:05:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/23 17:26:11 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/wait.h>

typedef struct	s_env
{
	char		*value;
	char		*key;
	struct s_env	*next_pt;
} t_env;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct	s_token
{
	char			*value;
	char			*valuebex;
	t_bool			var_exist;
	int				flag;
	int				ambiguous;
	int				quote;
	int				status;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;


typedef enum e_status
{
	DEFAULT,
	// QUOTE,
	SQUOTE,
	DQUOTE
}	t_status;

typedef enum e_type
{
	SPACES,
	PIPE,
	HEREDOC,
	WORD,
	TRUNC,
	VAR,
	QUOTE,
	NQUOTE,
	INPUT,
	APPEND,
	END
} e_type;

typedef struct	s_redir
{
	e_type			flag;
	char			*file;
	int			heredoc_fd;
	t_bool			expand_var;
	struct s_redir	*next;
} t_redir;

// typedef struct s_commands
// {
// 	char	*command;
// 	int		flag;
// 	struct s_commands	*next;
// 	struct s_commands	*prev;
// }	t_commands;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
	struct s_commands	*prev;
} t_command;


typedef struct	s_minishell 
{
	t_command	*cmds;
	t_env		*env;
	t_token		*tokens;
	pid_t		shel_pid;
	int			exit_status;
}	t_shell;

#include "helpers/libft.h"
#include "free_mem/free_m.h"
#include "parsing_am/parser.h"
#include "envirement/envirement.h"
#include "redirections/redirection.h"
#include "exec/execution.h"
#include "builtins/builtins.h"
#include "pipe/pipe.h"
#include "expander/expander.h"
#include "command_build/cmds.h"
#include "main/main.h"

#endif
