/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:09:18 by motelti           #+#    #+#             */
/*   Updated: 2025/05/03 11:44:33 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static int	add_redir(t_command *cmd, t_redir **last, int flag, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(*r));
	if (!r)
		return (1);
	r->flag = flag;
	r->file = ft_strdup(file);
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


static int	handle_redirection(t_command *cmd, t_redir **last, t_token **tok_ptr)
{
	t_token	*tok;
	int		flag;
	t_token	*next_tok;

	tok = *tok_ptr;
	flag = tok->flag;
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
	t_command	*cmd;

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

static int	process_token(t_build_info *info)
{
	int	ret;

	if (info->tok->flag == WORD)
		ret = handl_word(info->tok, &info->args, &info->arg_count);
	else if (info->tok->flag == INPUT || info->tok->flag == TRUNC
		  || info->tok->flag == APPEND || info->tok->flag == HEREDOC)
		ret = handle_redirection(info->cmd,
								 &info->last_redir,
								 &info->tok);
	else if (info->tok->flag == PIPE)
		ret = handle_pipe(&info->cmd,
						  &info->args,
						  &info->arg_count,
						  &info->last_redir);
	else
		ret = 0;
	return (ret);
}

t_command	*build_commands(t_token *tokens)
{
	t_build_info	info;

	if (init_build(tokens, &info))
		return (NULL);
	while (info.tok)
	{
		if (process_token(&info))
			return (NULL);
		info.tok = info.tok->next;
	}
	return (finish_build(&info));
}
