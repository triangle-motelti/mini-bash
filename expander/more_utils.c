/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:35:32 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 19:54:04 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	append_str(char **new, char *token, int start, t_shell *mini)
{
	(*new) = ft_realloc(*new, mini->j + 1, (mini->j + mini->i - start) + 1);
	while (start < mini->i)
	{
		(*new)[mini->j] = token[start];
		start++;
		(mini->j)++;
	}
}

void	single_quote(char *token, char **new, t_shell *mini)
{
	int	start;

	(mini->i)++;
	start = mini->i;
	while (token[mini->i] && token[mini->i] != '\'')
		(mini->i)++;
	append_str(new, token, start, mini);
	if (token[mini->i])
		(mini->i)++;
}

void	fill_splited(char **splited, t_token *token)
{
	int		i;
	t_token	*new;

	i = 1;
	while (splited[i])
	{
		new = ft_lstnew(splited[i], WORD);
		if (!new)
			return ;
		new->next = token->next;
		if (token->next)
			token->next->prev = new;
		token->next = new;
		new->prev = token;
		token = new;
		i++;
	}
}

void	invalid_or_not_expanded(char *newvalue, t_token *token)
{
	if (!newvalue)
	{
		free(token->value);
		token->value = ft_strdup("");
		token->ambiguous = 1;
	}
	else
	{
		free(token->value);
		token->value = newvalue;
	}
}

t_bool	dollar_expansion(char *token, t_shell *mini, char **new, int cap)
{
	if (token[(mini->i) + 1] == '\'' || token[(mini->i) + 1] == '"')
		(mini->i)++;
	else if (token[(mini->i) + 1] != '_'
		&& !ft_isalnum(token[(mini->i) + 1])
		&& token[(mini->i) + 1] != '?')
		append_character(new, &(mini->j), token[(mini->i)++]);
	else if ((token[mini->i])
		&& !(*new = handle_dollar(*new, token, mini)) && mini->i == cap)
		return (FALSE);
	return (TRUE);
}
