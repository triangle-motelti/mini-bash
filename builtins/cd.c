/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:10:03 by motelti           #+#    #+#             */
/*   Updated: 2025/06/06 17:49:01 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_pwd(t_shell *shell)
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
	if (new_pwd)
	{
		pwd_node = find_env_node(shell->env, "PWD");
		if (pwd_node)
			update_env_node(pwd_node, new_pwd);
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
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
		return (-1);
	}
	env_pwd(shell);
	return (0);
}
