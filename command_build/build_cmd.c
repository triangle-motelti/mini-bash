/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:09:18 by motelti           #+#    #+#             */
/*   Updated: 2025/05/02 15:25:22 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

// t_command *build_commands(t_token *tokens)
// {
//     t_command *cmd_list = NULL, *current_cmd = NULL;
//     t_redir *last_redir = NULL;
//     char **args = NULL;
//     int arg_count = 0;

//     while (tokens)
//     {
//         if (!current_cmd)
//         {
//             current_cmd = malloc(sizeof(t_command));
//             if (!current_cmd)
//                 return NULL;
//             current_cmd->args = NULL;
//             current_cmd->redirs = NULL;
//             current_cmd->next = NULL;
//             cmd_list = current_cmd;
//         }

//         if (tokens->flag == PIPE)
//         {
//             if (arg_count > 0)
//             {
//                 char **new_args = malloc((arg_count + 1) * sizeof(char *));
//                 if (!new_args)
//                     return NULL;
//                 int i = 0;
//                 while (i < arg_count)
//                 {
//                     new_args[i] = args[i];
//                     i++;
//                 }
//                 new_args[arg_count] = NULL;
//                 current_cmd->args = new_args;
//                 free(args);
//                 args = NULL;
//                 arg_count = 0;
//             }
//             current_cmd->next = malloc(sizeof(t_command));
//             if (!current_cmd->next)
//                 return NULL;
//             current_cmd = current_cmd->next;
//             current_cmd->args = NULL;
//             current_cmd->redirs = NULL;
//             current_cmd->next = NULL;
//             last_redir = NULL;
//         }
//         else if (tokens->flag == WORD)
//         {
//             char **new_args = malloc((arg_count + 1) * sizeof(char *));
//             if (!new_args)
//                 return NULL;
//             int i = 0;
//             while (i < arg_count)
//             {
//                 new_args[i] = args[i];
//                 i++;
//             }
//             new_args[arg_count] = strdup(tokens->value);
//             if (!new_args[arg_count])
//             {
//                 free(new_args);
//                 return NULL;
//             }
//             free(args);
//             args = new_args;
//             arg_count++;
//         }
//         else if (tokens->flag == INPUT || tokens->flag == TRUNC || tokens->flag == APPEND || tokens->flag == HEREDOC)
//         {
//             t_redir *redir = malloc(sizeof(t_redir));
//             if (!redir)
//                 return NULL;
//             redir->flag = tokens->flag;
//             tokens = tokens->next;
//             if (tokens && tokens->flag == WORD)
//             {
//                 redir->file = strdup(tokens->value);
//                 if (!redir->file)
//                 {
//                     free(redir);
//                     return NULL;
//                 }
//             }
//             else
//             {
//                 printf("syntax error near redirection\n");
//                 free(redir);
//                 return NULL;
//             }
//             redir->next = NULL;
//             if (!current_cmd->redirs)
//                 current_cmd->redirs = redir;
//             else
//                 last_redir->next = redir;
//             last_redir = redir;
//         }
//         tokens = tokens->next;
//     }

//     if (arg_count > 0)
//     {
//         char **new_args = malloc((arg_count + 1) * sizeof(char *));
//         if (!new_args)
//             return NULL;
//         int i = 0;
//         while (i < arg_count)
//         {
//             new_args[i] = args[i];
//             i++;
//         }
//         new_args[arg_count] = NULL;
//         current_cmd->args = new_args;
//         free(args);
//     }

//     return cmd_list;
// }


static t_command  *create_command(void)
{
	t_command  *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int  add_arg(char ***args, int *count, char *value)
{
	char    **new_args;
	int     i;

	new_args = malloc(sizeof(char *) * (*count + 2));
	if (!new_args)
		return (1);
	i = 0;
	while (i < *count)
	{
		new_args[i] = (*args)[i];
		i++;
	}
	new_args[i] = strdup(value);
	if (!new_args[i])
	{
		free(new_args);
		return (1);
	}
	new_args[i + 1] = NULL;
	free(*args);
	*args = new_args;
	(*count)++;
	return (0);
}

static int  finalize_args(t_command *cmd, char **args, int count)
{
	if (count > 0)
	{
		cmd->args = args;
		return (0);
	}
	free(args);
	return (0);
}

static int  add_redir(t_command *cmd, t_redir **last, int flag, char *file)
{
	t_redir *r;

	r = malloc(sizeof(*r));
	if (!r)
		return (1);
	r->flag = flag;
	r->file = strdup(file);
	if (!r->file)
		return (free(r), 1);
	r->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = r;
	else
		(*last)->next = r;
	*last = r;
	return (0);
}

static int  handle_word(t_token *tok, char ***args, int *count)
{
	return (add_arg(args, count, tok->value));
}

static int  handle_redirection(t_command *cmd, t_redir **last, t_token **tok_ptr)
{
	t_token  *tok = *tok_ptr;
	int       flag = tok->flag;
	t_token  *next_tok;

	next_tok = tok->next;
	if (!next_tok || next_tok->flag != WORD)
	{
		printf("syntax error near redirection\n");
		return (1);
	}
	if (add_redir(cmd, last, flag, next_tok->value))
		return (1);
	*tok_ptr = next_tok;
	return (0);
}

static int	handle_pipe(t_command **cmd_ptr, char ***args, int *count, t_redir **last)
{
	t_command  *cmd;

	cmd = *cmd_ptr;
	finalize_args(cmd, *args, *count);
	*args = NULL;
	*count = 0;
	cmd->next = create_command();
	if (!cmd->next)
		return (1);
	*cmd_ptr = cmd->next;
	*last = NULL;
	return (0);
}

t_command	*build_commands(t_token *tokens)
{
	t_command	*list;
	t_command	*cmd;
	t_redir		*last_redir;
	char		**args;
	int			arg_count;
	t_token		*tok;

	list = create_command();
	if (!list)
		return (NULL);
	cmd = list;
	last_redir = NULL;
	args = NULL;
	arg_count = 0;
	tok = tokens;
	while (tok)
	{
		if (tok->flag == WORD)
		{
			if (handle_word(tok, &args, &arg_count))
				return (NULL);
		}
		else if (tok->flag == INPUT || tok->flag == TRUNC
			  || tok->flag == APPEND || tok->flag == HEREDOC)
		{
			if (handle_redirection(cmd, &last_redir, &tok))
				return (NULL);
		}
		else if (tok->flag == PIPE)
		{
			if (handle_pipe(&cmd, &args, &arg_count, &last_redir))
				return (NULL);
		}
		tok = tok->next;
	}
	finalize_args(cmd, args, arg_count);
	return (list);
}

