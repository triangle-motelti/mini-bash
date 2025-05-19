/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:57:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/19 13:00:01 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	append_character(char **new, int *i, char c)
{
	(*new) = ft_realloc(*new, *i + 1, *i + 2);
	(*new)[(*i)] = c;
	(*i)++;
}

char	*handle_dollar(char *new, int *j, char *value, int *i, t_shell *mini)
{
	char	*extracted_value;
	char	*rep_value;
	int		k;
	int		len;

	k = 0;
	rep_value = NULL;
	extracted_value = malloc(ft_strlen(value) + 1);
	(*i)++;
	if (value[*i] == '$')
		extracted_value[k++] = value[(*i)++];
	while (is_limiter_expanders(value, *i))
		extracted_value[k++] = value[(*i)++];
	extracted_value[k] = '\0';
	rep_value = get_env_value(extracted_value, mini);
	if (!rep_value)
	{
		free(extracted_value);
		if (!new)
		{
			// free(value); // why freeing here is because when the value isn't expanded  it get replaced by null which means the first one get lost
			return (NULL);
		}
		return (new);
	}
	len = ft_strlen(rep_value);
	new = ft_realloc(new, *j + 1, *j + len + 1);
	k = 0;
	while (rep_value[k])
		append_character(&new, j, rep_value[k++]);
	free(extracted_value);
	free(rep_value);
	return (new);
}

char	*handle_dquote(char *new, int *j, char *value, int *i, t_shell *mini)
{
	char	quote;
	
	quote = value[*i];
	(*i)++;
	while (value[*i] && value[(*i)] != quote)
	{
		if (value[*i] == '$')
			new = handle_dollar(new, j, value, i, mini);
		else
			append_character(&new, j, value[(*i)++]);
	}
	if (value[*i] == '"')
	{
		// printf("added\n");
		// append_character(&new, j, value[*i]);
		(*i)++;
	}
	return (new);
}

char	*expand_each_token(char *token, int i, int j, t_shell *mini)
{
	char	*new;
	int		capacity;
	int		start;

	capacity = ft_strlen(token);
	new = NULL;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			start = i;
			while (token[i] && token[i] != '\'')
				i++;
			append_str(&new, token, start, i, &j);
			if (token[i])
				i++;
		}
		else if (token[i] == '"')
			new = handle_dquote(new, &j, token, &i, mini);
		else if (token[i] == '$')
		{
			if (!token[i + 1])
				append_character(&new, &j, token[i++]);
			if ((token[i]) && !(new = handle_dollar(new, &j, token, &i, mini)) && i == capacity)
				return (NULL);
		}
		else
			append_character(&new, &j, token[i++]);
	}
	append_character(&new, &j, '\0');
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
		printf("value in expander is %s\n", new_value);
		if (token->quote == QUOTE && new_value)
			rm_quotes(token);
		if (new_value && ft_strcmp(new_value, token->value) != 0)
		{
			free(token->value);
			token->value = new_value;
			ambiguous_case(token, mini);
			split_in_case(token, mini);
		}
		else
		{
			if (!new_value)
			{
				free(token->value);
				token->value = ft_strdup("");
				token->ambiguous = 1;
				token = token->next;
				continue ;
			}
			free(token->value);
			token->value = new_value;
		}
		token = token->next;
	}
	return (TRUE);
}
