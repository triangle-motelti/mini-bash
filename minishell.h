/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:05:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/26 09:52:52 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include "helpers/libft.h"
typedef struct	s_env
{
	char		*value;
	struct s_env	*next_pt;
} t_env;

typedef struct	s_token
{
	char	*value;
	struct s_token	*prev;
	int		flag;
	struct s_token	*next;
}	t_token;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_type
{
	SPACES,
	PIPE,
	HEREDOC,
	WORD,
	TRUNC,
	INPUT,
	APPEND,
	END,
	QUOTE
} e_type;

typedef struct	s_minishell 
{
	t_env	*env;
	char	**line;
	t_token	*tokens;
	int		fd_in;
	int		fd_out;

}	t_shell;

void	keep_tracking(t_shell *mini, int j, int start, char *input);
void	add_token(t_shell *mini, char *sep, int type);
int	handle_quotes(t_shell *mini, char *input, int *i);
t_token	*ft_lstnew(void *content, int type);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
char	quotes_syntax(char *input);
int	is_wspace(char input);
t_bool	tokenizer(t_shell *mini, char *input, int i);
int		is_separator(char *c, int i);
void 	exit_error(const char *msg);
void    free_tokens(t_token *tokens);
void    free_env(t_env *env);

#endif
