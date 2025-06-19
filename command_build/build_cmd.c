/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:09:18 by motelti           #+#    #+#             */
/*   Updated: 2025/06/19 12:17:54 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static char	*extract_delimiter(t_token *next_tok, int *expand_vars)
{
	char	*delimiter;

	delimiter = next_tok->value;
	*expand_vars = 1;
	if (next_tok->quote == QUOTE)
	{
		delimiter = process_quoted_delimiter(delimiter);
		if (!delimiter)
			return (NULL);
		*expand_vars = 0;
	}
	else
	{
		delimiter = ft_strdup(delimiter);
		if (!delimiter)
			return (NULL);
	}
	return (delimiter);
}

int	set_redir(t_command *cmd, t_redir **last, t_token **tok_ptr, t_shell *shell)
{
	t_token	*tok;
	int		flag;
	t_token	*next_tok;
	char	*delimiter;
	int		expand_vars;

	tok = *tok_ptr;
	flag = tok->flag;
	next_tok = tok->next;
	if (!next_tok || next_tok->flag != WORD)
	{
		ft_putstr_fd("mini-shell: syntax error near unexpected token `", 2);
		ft_putstr_fd(next_tok->value, 2);
		ft_putstr_fd("'\n", 2);
		return (shell->exit_status = 2, 1);
	}
	delimiter = extract_delimiter(next_tok, &expand_vars);
	if (!delimiter)
		return (1);
	if (add_redirc(cmd, last, flag, delimiter))
		return (1);
	set_heredoc_expand(*last, flag, expand_vars);
	free(delimiter);
	*tok_ptr = next_tok;
	return (0);
}

int	handle_pipe(t_command **cmd_ptr, char ***args, int *count, t_redir **last)
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

static int	process_token(t_build_info *info, t_shell *bash)
{
	int	ret;

	if (info->tok->flag == WORD)
		ret = handl_word(info->tok, &info->args, &info->arg_count);
	else if (info->tok->flag == INPUT || info->tok->flag == TRUNC
		|| info->tok->flag == APPEND || info->tok->flag == HEREDOC)
		ret = set_redir(info->cmd, &info->last_redir, &info->tok, bash);
	else if (info->tok->flag == PIPE)
		ret = handle_pipe(&info->cmd, &info->args, &info->arg_count,
				&info->last_redir);
	else
		ret = 0;
	return (ret);
}

t_command	*build_commands(t_token *tokens, t_shell *shell)
{
	t_build_info	info;

	if (init_build(tokens, &info))
		return (NULL);
	while (info.tok)
	{
		if (process_token(&info, shell))
			return (free_args(info.args), free_commands(info.list), NULL);
		info.tok = info.tok->next;
	}
	return (finish_build(&info));
}
