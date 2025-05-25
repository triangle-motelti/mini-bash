/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:33:44 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/25 14:05:19 by motelti          ###   ########.fr       */
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
	// t_token *tmp;

	if (!parser(mini))
	{
		clear_tokens(&mini->tokens);
		mini->exit_status = 1;
		return (FALSE);
	}
	if (!expander(mini))
	{
		clear_tokens(&mini->tokens);
		mini->exit_status = 1;
		return (FALSE);
	}
	// rm_quotes(mini->tokens);
	// tmp = mini->tokens;
	// while (tmp)
	// {
	// 	printf("tmp value is : %s and ambiguous is%d\n", tmp->value, tmp->ambiguous);
	// 	tmp = tmp->next;
	// }
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

int	shell(t_shell *mini)
{
	char		*input;
	t_command	*cmds;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (ft_putstr_fd("exit\n", STDERR_FILENO), mini->exit_status);
		add_history(input);
		if (!tokenizer(mini, input, 0, ft_strlen(input)) || !parsing_and_expanding(mini))
		{
			free(input);
			clear_tokens(&mini->tokens);
			continue ;
		}
		if (check_ambiguous_redirect(mini))
		{
			mini->exit_status = 1;
			free(input);
			clear_tokens(&mini->tokens);
			continue ;
		}
		cmds = build_commands(mini->tokens);
		if (cmds)
			execute_commands(mini, cmds);
		free_commands(cmds);
		clear_tokens(&mini->tokens);
		free(input);
	}
	return (mini->exit_status);
}

void	empty_env(t_shell *minishell)
{
	char	*pwd;
	char	*pwd_key;
	char	*shlvl_key;
	char	*shlvl_value;
	char	*path_key;
	char	*path_value;

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

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell minishell;
	memset(&minishell, 0, sizeof(t_shell));
	minishell.exit_status = 0;
	minishell.env = build_env_list(&minishell, envp);
	 if (!minishell.env)
		empty_env(&minishell);
	if (!shell(&minishell))
		return (free_env_list(minishell.env), minishell.exit_status);
	return (free_env_list(minishell.env), minishell.exit_status);
}
