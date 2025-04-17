#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

int	check_command(t_shell *mini)
{
	//here you gonna execute the commands found in mini->line
}

int shell(t_shell *mini)
{
	char *input;

	input = NULL;
	while (1)
	{
		mini->line = readline("minishell> ");
		if (!input)
			return (0);
		check_command(mini);
	}
	free(input);
	return 1;
}

int	main(int argc, char **v, char **env)
{
	(void) argc;//check for errors
	(void) v;//do not accept more that one argument
	(void) env;
	t_shell	minishell;

	// copy_env(&minishell, env);
	memset(&minishell, 0, sizeof(t_shell));
	if (!shell(&minishell))
		return 1;
}
