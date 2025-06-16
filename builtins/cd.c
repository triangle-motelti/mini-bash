/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:03 by motelti           #+#    #+#             */
/*   Updated: 2025/06/16 18:30:57 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_parent_dir(char *current_pwd)
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

void	env_pwd(t_shell *shell, char *path)
{
	t_env	*pwd_node;
	t_env	*oldpwd_node;
	char	*new_pwd;

	pwd_node = find_env_node(shell->env, "PWD");
	if (pwd_node)
	{
		oldpwd_node = find_env_node(shell->env, "OLDPWD");
		if (oldpwd_node)
			update_env_node(oldpwd_node, pwd_node->value);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		new_pwd = construct_pwd_path(shell, path);
	if (new_pwd)
	{
		if (pwd_node)
			update_env_node(pwd_node, new_pwd);
		else
			append_env_node(shell, ft_strdup("PWD"), new_pwd);
		free(new_pwd);
	}
}

int	cd(t_shell *shell, int ac, char **args)
{
	if (ac != 2)
	{
		ft_putstr_fd("minishell: cd: missing path argument\n", STDERR_FILENO);
		shell->exit_status = 1;
		return (-1);
	}
	if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		shell->exit_status = 1;
		return (-1);
	}
	env_pwd(shell, args[1]);
	shell->exit_status = 0;
	return (0);
}
