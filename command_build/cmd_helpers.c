/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:32:24 by motelti           #+#    #+#             */
/*   Updated: 2025/06/28 16:48:41 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

int	init_build(t_token *tokens, t_build_info *info)
{
	info->list = create_command();
	if (!info->list)
		return (1);
	info->cmd = info->list;
	info->last_redir = NULL;
	info->args = NULL;
	info->arg_count = 0;
	info->tok = tokens;
	return (0);
}

int	finalize_args(t_command *cmd, char **args, int count)
{
	if (count > 0)
	{
		cmd->args = args;
		return (0);
	}
	free(args);
	return (0);
}

int	handl_word(t_token *tok, char ***args, int *count)
{
	if (add_arg(args, count, tok->value))
		return (free_args(*args), *args = NULL, 1);
	return (0);
}

int	add_redirc(t_command *cmd, t_redir **last, int flag, char *delim)
{
	if (add_redir(cmd, last, flag, delim))
	{
		free(delim);
		return (1);
	}
	return (0);
}

void	set_heredoc_expand(t_redir *last, int flag, int expand_vars)
{
	if (flag == HEREDOC)
		last->expand_var = expand_vars;
}
