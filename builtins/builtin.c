/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:11:14 by motelti           #+#    #+#             */
/*   Updated: 2025/06/27 22:49:43 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->flag == WORD && current->quote == NQUOTE
			&& current->value[0] == '\0')
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				*tokens = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->value);
			free(current->valuebex);
			free(current);
		}
		current = next;
	}
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0);
}

char	*get_parent_dir(char *current_pwd)
{
	char	*last_slash;
	size_t	len;
	char	*new_pwd;

	last_slash = ft_strrchr(current_pwd, '/');
	if (!last_slash)
		return (ft_strdup(current_pwd));
	if (last_slash == current_pwd)
		return (ft_strdup("/"));
	len = last_slash - current_pwd;
	new_pwd = ft_strndup(current_pwd, len);
	return (new_pwd);
}

char	*construct_pwd_path(t_shell *shell, char *path)
{
	t_env	*pwd_node;
	char	*current_pwd;
	char	*new_pwd;

	pwd_node = find_env_node(shell->env, "PWD");
	if (!pwd_node || !pwd_node->value)
		return (ft_strdup(path));
	current_pwd = pwd_node->value;
	if (path[0] == '/')
		return (ft_strdup(path));
	if (ft_strcmp(path, "..") == 0)
		return (get_parent_dir(current_pwd));
	new_pwd = ft_strjoin_sep(current_pwd, path, "/");
	return (new_pwd);
}
