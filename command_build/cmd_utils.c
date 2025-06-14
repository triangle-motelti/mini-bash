/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:46:07 by motelti           #+#    #+#             */
/*   Updated: 2025/06/14 11:30:35 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

char	*process_quoted_delimiter(char *delimiter)
{
	size_t	len;

	if (delimiter[0] == '\'' || delimiter[0] == '"')
	{
		len = ft_strlen(delimiter);
		if (len >= 2 && delimiter[len - 1] == delimiter[0])
			return (ft_strndup(delimiter + 1, len - 2));
		else
		{
			printf("syntax error: unclosed quote in delimiter\n");
			return (NULL);
		}
	}
	else
		return (ft_strdup(delimiter));
}

int	add_redir(t_command *cmd, t_redir **last, int flag, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(*r));
	if (!r)
		return (1);
	r->flag = flag;
	r->file = ft_strdup(file);
	if (!r->file)
		return (free(r), 1);
	r->expand_var = 0;
	r->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = r;
	else
		(*last)->next = r;
	*last = r;
	return (0);
}

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

t_command	*finish_build(t_build_info *info)
{
	finalize_args(info->cmd, info->args, info->arg_count);
	return (info->list);
}
