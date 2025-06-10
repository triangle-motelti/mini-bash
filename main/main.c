/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:33:44 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/10 15:45:02 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	handle_empty_or_invalid_input(t_shell *mini, char *input)
{
	if (*input == '\0')
	{
		free(input);
		return (1);
	}
	add_history(input);
	if (!tokenizer(mini, input, 0, ft_strlen(input))
		|| !parsing_and_expanding(mini))
	{
		free(input);
		clear_tokens(&mini->tokens);
		return (1);
	}
	if (check_ambiguous_redirect(mini))
	{
		mini->exit_status = 1;
		free(input);
		clear_tokens(&mini->tokens);
		return (1);
	}
	return (0);
}

static void	process_input(t_shell *mini, char *input)
{
	t_command	*cmds;

	if (handle_empty_or_invalid_input(mini, input))
		return ;
	cmds = build_commands(mini->tokens, mini);
	if (cmds)
		execute_commands(mini, cmds);
	free_commands(cmds);
	clear_tokens(&mini->tokens);
	free(input);
}

int	shell(t_shell *mini)
{
	char	*input;

	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (g_received_signal == SIGINT)
		{
			mini->exit_status = 130;
			g_received_signal = 0;
		}
		if (!input)
			return (ft_putstr_fd("exit\n", STDERR_FILENO), mini->exit_status);
		process_input(mini, input);
	}
	return (mini->exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	minishell;

	(void)ac;
	(void)av;
	ft_memset(&minishell, 0, sizeof(t_shell));
	minishell.exit_status = 0;
	minishell.env = build_env_list(&minishell, envp);
	if (!minishell.env)
		empty_env(&minishell);
	if (!shell(&minishell))
		return (free_env_list(minishell.env), minishell.exit_status);
	return (free_env_list(minishell.env), minishell.exit_status);
}
