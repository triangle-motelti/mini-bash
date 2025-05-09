/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:57:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/09 10:24:34 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	append_character(char *new, int *i, char c)
{
	new[(*i)++] = c;
}

char	*handle_dollar(char *new, int *j, char *value, int *i, t_shell *mini)
{
	int		start;
	char	*extracted_value;
	char	*rep_value;
	int		k;
	int		len;
	char	*res;

	start = (*i)++;
	k = 0;
	extracted_value = malloc(ft_strlen(value) + 1);
	// is_limiter_expanders(value, *i);
	while (is_limiter_expanders(value, *i))// i need to use ft_realloc;
		extracted_value[k++] = value[(*i)++];
	extracted_value[k] = '\0';
	rep_value = get_env_value(extracted_value, mini);// here rep_value will point to the string i think i need to calculate its length ,
	// free(extracted_value);
	if (!rep_value)
		return (new);
	len = ft_strlen(rep_value);
	k = 0;
	res = ft_realloc(new, *j + 1, *j + len + 1);
	new = res;
	while (rep_value[k])
	{
		append_character(new, j, rep_value[k]);
		k++;
	}
	return (new);
}

char	*handle_dquote(char *new, int *j, char *value, int *i, t_shell *mini)
{
	(*i)++;
	while (value[*i] && value[*i] != '"')
	{
		if (value[*i] == '$')
			new = handle_dollar(new, j, value, i, mini);
		else
			append_character(new, j, value[(*i)++]);
	}
	if (value[*i] == '"')
		(*i)++;
	return (new);
}

char	*expand_each_token(char *token, int i, int j, t_shell *mini)
{
	char	*new;

	new = malloc(1);
	new[0] = '\0';
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] != '\'')
				append_character(new, &j, token[i++]);
			if (token[i] == '\'')
				i++;
		}
		else if (token[i] == '"')
			new = handle_dquote(new, &j, token, &i, mini);
		else if (token[i] == '$')
			new = handle_dollar(new, &j, token, &i, mini);
		else
			append_character(new, &j, token[i++]);
	}
	new[j] = '\0';
	return (new);
}

t_bool	expander(t_shell *mini)
{
	t_token	*token;
	char	*new_value;
	int		i;

	token = mini->tokens;
	while (token)
	{

		new_value = expand_each_token(token->value, 0, 0, mini);
		// printf("value in expander is %s\n", new_value);
		if (new_value)
		{
			free(token->value);
			token->value = new_value;
		}
		printf("token's value is : %s\n", token->value);
		token = token->next;
	}
	return (TRUE);
}
