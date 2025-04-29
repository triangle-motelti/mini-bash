/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:41:55 by motelti           #+#    #+#             */
/*   Updated: 2025/04/27 22:37:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env
{
	char		*value;
	char		*key;
	struct s_env	*next_pt;
} t_env;

typedef struct	s_minishell 
{
	t_env	*env;
	char	*line;
	int		exit_status;
	int		pipe_in;
	int		pipe_out;
}	t_shell;

typedef struct	s_pipe_info
{
	int	is_first;
	int	is_last;
	int	prev_fd;
	int	cur_fd[2];
}	t_pipe_info;

# include "helpers/libft.h"
# include "parser/parser.h"
# include "envp/envp.h"
# include "pipe/pipe.h"
# include "mainshell/main.h"
# include "excution/excution.h"
# include "builtins/builtins.h"


#endif
