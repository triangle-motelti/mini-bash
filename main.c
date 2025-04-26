/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:33:44 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/26 09:45:28 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void check_command(t_shell *mini)
{
	if (!mini->line || !mini->line[0])
		return;	
	if (strcmp(mini->line[0], "exit") == 0) {
		// free_tokens(mini->line);
		free_env(mini->env);
		exit(0);
	}
	pid_t pid = fork();
	if (pid < 0) exit_error("fork failed");
	if (pid == 0) {
		execvp(mini->line[0], mini->line);
		perror("execvp");
		exit(1);
	} else {
		int status;
		waitpid(pid, &status, 0);
	}
}

// print error and exit
void exit_error(const char *msg)
{
	perror(msg);
	exit(1);
}

void	copy_env(t_shell *mini, char **env, int i)
{
	t_env	*node;
	t_env	*head;
	t_env	*tmp;

	head = NULL;
	tmp = NULL;
	while (env[++i])//create a linked list
	{
		node = malloc(sizeof(*node));
		if (!node)
			exit_error("malloc");
		node->value = strdup(env[i]);
		if (!node->value)
		{
			free(node);
			exit_error("nodes error\n");
		}
		node->next_pt = NULL;
		if (!head)
			head = node;
		else
			tmp->next_pt = node;
		tmp = node;
	}
	mini->env = head;//setting the env to point into the head of the list
}

int shell(t_shell *mini)
{
	char *input;

	input = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (0);
		if (input == NULL)
			exit_error("empty prompt");
		add_history(input);
		if (!tokenizer(mini, input, 0))
		{
			free_tokens(mini->tokens);
			continue ;
		}
		while (mini->tokens)
		{
			printf("value is %s // and flag is %d\n", mini->tokens->value, mini->tokens->flag);
			mini->tokens = mini->tokens->next;
		}
		check_command(mini);
		free(input);
	}
	return (1);
}

int	main(int argc, char **v, char **env)// ./minishell ,,,,,,,,,,,,,, read from stdin
{
	t_shell	minishell;

	(void) v;
	if (argc != 1)
		exit_error("arguments not allowed");
	memset(&minishell, 0, sizeof(t_shell));
	copy_env(&minishell, env, -1);//done using linked list
	if (!shell(&minishell))
	{
		exit_error("error in shell()\n");
		
	}
}
