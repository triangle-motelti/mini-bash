/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:33:44 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/19 22:54:44 by mohamed          ###   ########.fr       */
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
		return (FALSE);
	}
	if (!expander(mini))
	{
		clear_tokens(&mini->tokens);
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
			return (ft_putstr_fd("exit\n", STDERR_FILENO), 0);
		add_history(input);
		mini->exit_status = 0;
		if (!tokenizer(mini, input, 0, ft_strlen(input)) || !parsing_and_expanding(mini))
		{
			free(input);
			clear_tokens(&mini->tokens);
			continue ;
		}
		check_ambiguous_redirect(mini);
		if (mini->exit_status == 1)
		{
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
	return (1);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell minishell;
	memset(&minishell, 0, sizeof(t_shell));
	minishell.shel_pid = getpid();
	// printf("pid is :%d\n", minishell.shel_pid);
	minishell.env = build_env_list(&minishell, envp);
	if (!minishell.env)
	{
		ft_putstr_fd( "Failed to initialize environment\n", STDERR_FILENO);
		return (1);
	}
	if (!shell(&minishell))
		return (free_env_list(minishell.env), 1);
	return (free_env_list(minishell.env), 0);
}
