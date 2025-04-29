/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:30:05 by motelti           #+#    #+#             */
/*   Updated: 2025/04/21 16:11:18 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

char	**find_path(char *const *envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static	char	*search_in_env_path(char *cmd, char **env_path)
{
	char	*join;
	char	*cmd_path;
	int		i;

	i = 0;
	while (env_path[i])
	{
		join = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(join, cmd);
		free(join);
		if (access(cmd_path, X_OK) == 0)
		{
			free_split(env_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_split(env_path);
	return (NULL);
}

char	*path_cmd(char *cmd, char *const *envp)
{
	char	**env_path;
	char	*cmd_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	env_path = find_path(envp);
	if (env_path)
		return (search_in_env_path(cmd, env_path));
	else
	{
		cmd_path = ft_strjoin("./", cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}
