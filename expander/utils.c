/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:52:52 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 18:03:57 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_env_value(char *value, t_shell *mini)
{
	t_env	*tmp_env;
	char	*state;

	if (!value || !value[0])
		return (NULL);
	tmp_env = mini->env;
	if (ft_strcmp(value, "?") == 0)
	{
		state = ft_itoa(mini->exit_status);
		return (state);
	}
	while (tmp_env)
	{
		if (ft_strcmp(value, tmp_env->key) == 0)
			return (ft_strdup(tmp_env->value));
		tmp_env = tmp_env->next_pt;
	}
	return (NULL);
}

t_bool	is_limiter_expanders(char *value, int i)
{
	if (i >= 1 && value[i] == '?' && value[i - 1] == '$')
		return (TRUE);
	if (i >= 1 && value[i - 1] == '?')
		return (FALSE);
	if ((ft_isalpha((unsigned int)value[i]) || value[i] == '_'))
		return (TRUE);
	if ((ft_isalnum((unsigned int)value[i]) || value[i] == '_'))
		return (TRUE);
	return (FALSE);
}

void	split_in_case(t_token *token, t_shell *mini)
{
	char	**split;

	(void)mini;
	if ((token->quote == QUOTE) || (ft_strchr(token->value, ' ') == NULL))
		return ;
	split = NULL;
	if (token->quote == NQUOTE && (ft_strchr(token->value, ' ') != NULL))
		split = ft_split(token->value, ' ');
	if (!split || !split[1])
	{
		free(split[0]);
		free(split);
		return ;
	}
	free(token->value);
	token->value = split[0];
	fill_splited(split, token);
	free(split);
}

void	pass_quote(t_token *tkn, char **new_str, int *j, int *i)
{
	char	*value;
	char	quote;

	value = tkn->value;
	quote = tkn->value[*i];
	(*i)++;
	while (value[*i] && value[*i] != quote)
	{
		(*new_str)[*j] = value[*i];
		(*i)++;
		(*j)++;
	}
	if (value[*i] == quote)
		(*i)++;
}

void	rm_quotes(t_token *token)
{
	t_token	*tmp_token;
	int		i;
	char	*new_str;
	int		j;

	tmp_token = token;
	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(tmp_token->value) + 1);
	if (!new_str)
		return ;
	while (tmp_token->value[i])
	{
		if (tmp_token->value[i] == '\'' || tmp_token->value[i] == '"')
			pass_quote(tmp_token, &new_str, &j, &i);
		else
			new_str[j++] = tmp_token->value[i++];
	}
	new_str[j] = '\0';
	free(tmp_token->value);
	tmp_token->value = new_str;
}
