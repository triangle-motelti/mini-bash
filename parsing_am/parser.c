/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:34:12 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/21 11:08:43 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	check_pipe(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp->flag == PIPE)
	{
		printf("mini-shell: syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	while (tmp)
	{
		if ((tmp->flag == PIPE && !tmp->next)
			|| (tmp->flag == PIPE && tmp->next->flag == PIPE)
			|| (tmp->flag == PIPE && tmp->next->flag == END))
		{
			printf("mini-shell: syntax error near unexpected token `|'\n");
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

int	count_herdoc(t_token *tmp_tkn)
{
	int	cnt;

	cnt = 0;
	while (tmp_tkn)
	{
		if (tmp_tkn->flag == HEREDOC)
			cnt++;
		tmp_tkn = tmp_tkn->next;
	}
	return (cnt);
}

t_bool	check_redirections(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if ((tmp->flag == HEREDOC && !tmp->next)
			|| (tmp->flag == TRUNC && !tmp->next)
			|| (tmp->flag == INPUT && !tmp->next)
			|| (tmp->flag == APPEND && !tmp->next))
		{
			printf("mini: syntax error near unexpected token `redirection'\n");
			return (FALSE);
		}
		if (count_herdoc(tmp) > 16)
		{
			printf("mini: maximum here-document count exceeded\n");
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

t_bool	parser(t_shell *mini)
{
	t_token	*tmp;
	int		i;

	tmp = mini->tokens;
	while (tmp)
	{
		i = 0;
		tmp->quote = NQUOTE;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '\'' || tmp->value[i] == '"')
			{
				tmp->quote = QUOTE;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	if (!mini->tokens)
		return (FALSE);
	if (!check_pipe(mini->tokens) || !check_redirections(mini->tokens))
		return (FALSE);
	return (TRUE);
}
