/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:46:07 by motelti           #+#    #+#             */
/*   Updated: 2025/05/26 12:36:24 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
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

int	add_arg(char ***args, int *count, char *value)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (*count + 2));
	if (!new_args)
		return (1);
	i = 0;
	while (i < *count)
	{
		new_args[i] = (*args)[i];
		i++;
	}
	new_args[i] = ft_strdup(value);
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

int	handl_word(t_token *tok, char ***args, int *count)
{
	if (add_arg(args, count, tok->value))
		return (free_args(*args), *args = NULL, 1);
	return (0);
}

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

t_command	*finish_build(t_build_info *info)
{
	finalize_args(info->cmd, info->args, info->arg_count);
	return (info->list);
}