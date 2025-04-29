/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:41:13 by motelti           #+#    #+#             */
/*   Updated: 2025/04/29 10:16:58 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void check_command(t_shell *mini)
{
	char	**commands;
	int		cmd_count;

	commands = split_pipeline(mini->line);
	if (!commands)
		return ;
	cmd_count = count_cmds(commands);
	if (cmd_count > 1)
		execute_pipeline(mini, commands);
	else
	{
		char **args = parse_input(mini, mini->line);
		if (args && args[0])
			execute_single_command(mini, args);
		free_args(args);
	}
	free_commands(commands);
}

static int	shell(t_shell *mini, int ac, char **av, char **envp)
{
	char	*line;

	while (1)
	{
		mini->line = readline("minishell> ");
		if (!mini->line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			return (0);
		}
		add_history(mini->line);
		check_command(mini);
		free(mini->line);
		mini->line = NULL;
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_shell	minishell;

	ft_memset(&minishell, 0, sizeof(t_shell));
	minishell.env = build_env_list(&minishell, envp);
	if (!minishell.env)
	{
		ft_putstr_fd("Failed to initialize environment\n", STDERR_FILENO);
		return (1);
	}
	if (!shell(&minishell, ac, av, envp))
		return (1);
	return (0);
}
