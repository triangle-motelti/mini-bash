/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:34:12 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/01 20:56:49 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	check_pipe(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp->flag == PIPE)
	{
		printf("mini-shell: syntax error near unexpected token f `|'\n");
		return (FALSE);
	}
	while (tmp)
	{
		if (tmp->flag == PIPE && !tmp->next
			|| tmp->flag == PIPE && tmp->next->flag == PIPE
			|| tmp->flag == PIPE && tmp->next->flag == END)
		{
			printf("mini-shell: syntax error near unexpected token `|'\n");
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

t_bool	check_redirections(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->flag == HEREDOC && !tmp->next || tmp->flag == TRUNC && !tmp->next 
			|| tmp->flag == INPUT && !tmp->next || tmp->flag == APPEND && !tmp->next)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

void	check_dollar(t_shell *mini)
{
	t_token	*tmp;

	tmp = mini->tokens;
	//if found replace the type of node to VAR
	// while (condition)
	// {
		
	// }
	
}

t_bool	parser(t_shell *mini)
{
	// t_token	*tmp;

	// tmp = mini->tokens;
	// if (ft_strncmp(tmp->value, "|", ft_strlen(tmp->value)) == 0)
	// {
	// 	printf("mini-shell: syntax error near unexpected token `|'\n");
	// 	return (FALSE);
	// }
	if (!mini->tokens)
		return (FALSE);
	if (!check_pipe(mini->tokens))
		return (FALSE);
	if (!check_redirections(mini->tokens))
		return (FALSE);
	check_dollar(mini);
		// return (FALSE);
	return (TRUE);
}
