/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:05:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 15:21:33 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <errno.h>
# include <ctype.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <sys/wait.h>

# include "structs.h"
# include "helpers/libft.h"
# include "free_mem/free_m.h"
# include "parsing_am/parser.h"
# include "envirement/envirement.h"
# include "redirections/redirection.h"
# include "exec/execution.h"
# include "signals/signal.h"
# include "builtins/builtins.h"
# include "pipe/pipe.h"
# include "expander/expander.h"
# include "command_build/cmds.h"
# include "main/main.h"

#endif
