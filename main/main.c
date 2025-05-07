/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:33:44 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/04 10:25:21 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bool	parsing_and_expanding(t_shell *mini)
{
	if (!parser(mini))
	{
		clear_tokens(&mini->tokens);
		return (FALSE);
	}
	if (!expander(mini))
	{
		clear_tokens(&mini->tokens);
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

int	shell(t_shell *mini)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (ft_putstr_fd("exit\n", STDERR_FILENO), 0);
		add_history(input);
		if (!tokenizer(mini, input, 0) || !parsing_and_expanding(mini))
		{
			free_tokens(mini->tokens);
			mini->tokens = NULL;
			free(input);
			continue ;
		}
		t_command *cmds = build_commands(mini->tokens);
		if (cmds)
			execute_commands(mini, cmds);
		free_commands(cmds);
		free_tokens(mini->tokens);
		mini->tokens = NULL;
		free(input);
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_shell minishell;
    memset(&minishell, 0, sizeof(t_shell));
	minishell.env = build_env_list(&minishell, envp);
    if (!minishell.env)
    {
        ft_putstr_fd( "Failed to initialize environment\n", STDERR_FILENO);
        return (1);
    }
    if (!shell(&minishell))
        return (1);
    return (0);
}
