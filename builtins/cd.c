/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:03 by motelti           #+#    #+#             */
/*   Updated: 2025/06/28 10:11:41 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	{
		perror("minishell: cd: error retrieving current directory");
		new_pwd = construct_pwd_path(shell, path);
	}
	if (new_pwd)
	{
		if (pwd_node)
			update_env_node(pwd_node, new_pwd);
		else
			append_env_node(shell, ft_strdup("PWD"), new_pwd);
		free(new_pwd);
	}
}

static int	cd_home(t_shell *shell, t_env *home_env)
{
	if (home_env == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (shell->exit_status = 1, -1);
	}
	if (chdir(home_env->value) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(home_env->value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		return (perror(""), shell->exit_status = 1, -1);
	}
	env_pwd(shell, home_env->value);
	return (0);
}

static int	cd_path(t_shell *shell, char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		return (perror(""), shell->exit_status = 1, -1);
	}
	env_pwd(shell, path);
	return (0);
}

int	cd(t_shell *shell, int ac, char **args)
{
	t_env	*home_env;

	home_env = find_env_node(shell->env, "HOME");
	if (ac == 1)
		return (cd_home(shell, home_env));
	else if (ac != 2)
	{
		ft_putstr_fd("minishell: cd: missing path argument\n", 2);
		return (shell->exit_status = 1, -1);
	}
	else
		return (cd_path(shell, args[1]));
	return (shell->exit_status = 0, 0);
}
