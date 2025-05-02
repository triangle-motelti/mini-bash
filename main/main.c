/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:33:44 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/02 14:45:33 by motelti          ###   ########.fr       */
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

void execute_commands(t_shell *shell, t_command *cmds)
{
	int cmd_count = 0;
	t_command *tmp = cmds;
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

// int	shell(t_shell *mini)
// {
// 	char *input;

// 	input = NULL;
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			perror("read: ");
// 			continue ;
// 		}
// 		add_history(input);
// 		if (!tokenizer(mini, input, 0))
// 		{
// 			clear_tokens(&mini->tokens);
// 			continue ;
// 		}
// 		if (!parsing_and_expanding(mini))
// 			continue ;
// 		int i = 0;
// 		while (mini->tokens)
// 		{
// 			printf("cmds are : %s\n", mini->tokens->value);
// 			mini->tokens = mini->tokens->next;
// 		}
// 		clear_tokens(&mini->tokens);
// 	}
// 	return (1);
// }

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

// int	main(int ac, char **av, char **env)
// {
// 	t_shell	minishell;

// 	(void) av;
// 	memset(&minishell, 0, sizeof(t_shell));
// 	copy_env(&minishell, env, -1);//done using linked list
// 	if (!shell(&minishell))
// 	{
// 		printf("error in shell()\n");
		
// 	}
// }

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_shell minishell;
    memset(&minishell, 0, sizeof(t_shell));
    // copy_env(&minishell, envp);
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
