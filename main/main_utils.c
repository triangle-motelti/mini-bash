/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:31:30 by motelti           #+#    #+#             */
/*   Updated: 2025/06/06 13:39:40 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next_pt;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_bool	parsing_and_expanding(t_shell *mini)
{
	if (!parser(mini))
	{
		clear_tokens(&mini->tokens);
		mini->exit_status = 1;
		return (FALSE);
	}
	mini->tkn = mini->tokens;
	if (!expander(mini))
	{
		clear_tokens(&mini->tokens);
		mini->exit_status = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	execute_commands(t_shell *shell, t_command *cmds)
{
	int			cmd_count;
	t_command	*tmp;

	cmd_count = 0;
	tmp = cmds;
	while (tmp)
	{
		cmd_count++;
		tmp = tmp->next;
	}
	if (cmd_count == 1)
		execute_single_command(shell, cmds);
	else
		execute_pipeline(shell, cmds);
}

void	pwd_env(t_shell *minishell)
{
	char	*pwd;
	char	*pwd_key;

	if (!find_env_node(minishell->env, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			pwd_key = ft_strdup("PWD");
			if (pwd_key)
				append_env_node(minishell, pwd_key, pwd);
			free(pwd);
		}
	}
}

void	empty_env(t_shell *minishell)
{
	char	*shlvl_key;
	char	*shlvl_value;
	char	*path_key;
	char	*path_value;

	pwd_env(minishell);
	if (!find_env_node(minishell->env, "SHLVL"))
	{
		shlvl_key = ft_strdup("SHLVL");
		shlvl_value = ft_strdup("1");
		if (shlvl_key && shlvl_value)
			append_env_node(minishell, shlvl_key, shlvl_value);
		free(shlvl_value);
	}
	if (!find_env_node(minishell->env, "PATH"))
	{
		path_key = ft_strdup("PATH");
		path_value = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
		if (path_key && path_value)
			append_env_node(minishell, path_key, path_value);
		free(path_value);
	}
}
