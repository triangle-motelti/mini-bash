/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:17:03 by motelti           #+#    #+#             */
/*   Updated: 2025/06/06 13:38:19 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next_pt;
}					t_env;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_token
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
}	t_type;

typedef struct s_redir
{
	t_type			flag;
	char			*file;
	int				heredoc_fd;
	t_bool			expand_var;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
	struct s_commands	*prev;
}	t_command;

typedef struct s_minishell
{
	t_command	*cmds;
	t_env		*env;
	t_token		*tokens;
	t_token		*tkn;
	int			i;
	int			j;
	int			exit_status;
}	t_shell;

#endif
