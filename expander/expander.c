/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:57:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/28 22:11:51 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	append_character(char **new, int *i, char c)
{
	(*new) = ft_realloc(*new, *i + 1, *i + 2);
	(*new)[(*i)] = c;
	(*i)++;
}

char	*handle_dollar(char *new, char *value, t_shell *mini)
{
	char	*extracted_value;
	char	*rep_value;
	int		k;
	int		len;

	rep_value = NULL;
	(mini->i)++;
	extracted_value = norm_for_dollar_hand(value, mini);
	rep_value = get_env_value(extracted_value, mini);
	if (!rep_value)
	{
		free(extracted_value);
		if (!new)
			return (NULL);
		return (new);
	}
	len = ft_strlen(rep_value);
	new = ft_realloc(new, mini->j + 1, mini->j + len + 1);
	k = 0;
	while (rep_value[k])
		append_character(&new, &(mini->j), rep_value[k++]);
	free(extracted_value);
	free(rep_value);
	return (new);
}

char	*handle_dquote(char *new, char *value, t_shell *mini)
{
	char	quote;

	quote = value[mini->i];
	append_character(&new, &(mini->j), value[mini->i]);
	(mini->i)++;
	while (value[mini->i] && value[mini->i] != quote)
	{
		if (value[mini->i] == '$')
		{
			if (value[(mini->i) + 1] == '$')
				mini->i += 2;
			else if (value[(mini->i) + 1] && (value[(mini->i) + 1] != '"'))
				new = handle_dollar(new, value, mini);
			else
				append_character(&new, &(mini->j), value[(mini->i)++]);
		}
		else
			append_character(&new, &(mini->j), value[(mini->i)++]);
	}
	if (value[mini->i] == '"')
		append_character(&new, &(mini->j), value[(mini->i)++]);
	return (new);
}

char	*expand_each_token(char *token, int i, int j, t_shell *mini)
{
	char	*new;
	int		capacity;

	capacity = ft_strlen(token);
	new = NULL;
	mini->i = i;
	mini->j = j;
	while (token[mini->i])
	{
		if (token[mini->i] == '\'')
			single_quote(token, &new, mini);
		else if (token[mini->i] == '"')
			new = handle_dquote(new, token, mini);
		else if (token[mini->i] == '$')
		{
			if (!token[(mini->i) + 1])
				append_character(&new, &(mini->j), token[(mini->i)++]);
			else if (!dollar_expansion(token, mini, &new, capacity))
				return (NULL);
		}
		else
			append_character(&new, &(mini->j), token[(mini->i)++]);
	}
	append_character(&new, &(mini->j), '\0');
	return (new);
}

t_bool	expander(t_shell *mini)
{
	t_token	*token;
	char	*new_value;

	token = mini->tokens;
	new_value = NULL;
	while (token)
	{
		if ((!token->prev || (ft_strcmp(token->prev->value, "<<" ) != 0)))
			new_value = expand_each_token(token->value, 0, 0, mini);
		else
			new_value = ft_strdup(token->value);
		if (new_value && ft_strcmp(new_value, token->value) != 0)
		{
			free(token->value);
			token->value = new_value;
			ambiguous_case(token, mini);
			split_in_case(token, mini);
		}
		else
			invalid_or_not_expanded(new_value, token);
		rm_quotes(token);
		token = token->next;
	}
	return (TRUE);
}
