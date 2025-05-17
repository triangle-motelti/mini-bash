/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:52:52 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/16 19:26:56 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_env_value(char *value, t_shell *mini)
{
	t_env	*tmp_env;
	char	*state;
	char	*pid_manager;

	if (!value || !value[0])
		return (NULL);
	tmp_env = mini->env;
	if (ft_strcmp(value, "?") == 0)
	{
		state = ft_itoa(mini->exit_status);
		return (state);
	}
	if ((pid_manager = check_dollar(value, mini->env)) != NULL)
		return (ft_strdup(pid_manager));
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
	if (i >= 2)
	{
		if ((value[i - 2] == '$') && (value[i - 1] == '$') && (i < 3 || value[i - 3] != '$'))
			return (FALSE);
	}
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
	int		pt;
	int		i;
	t_token	*new;

	pt = check_environements(token->value, mini);
	if (pt == 0)
		return ;
	split = ft_split(token->value, token->value[pt]);
	if (!split || !split[1])
	{
		free(split);
		return ;
	}
	printf("split 1 is : %s\n" , split[1]);
	free(token->value);
	token->value = ft_strdup(split[0]);
	i = 1;
	while (split[i])
	{
		new = ft_lstnew(split[i], WORD);
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
	free(split);
}

void	pass_quote(char quote, char *value, char **new_str, int *j, int *i)
{
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
			pass_quote(tmp_token->value[i], tmp_token->value, &new_str, &j, &i);
		else
			new_str[j++] = tmp_token->value[i++];
	}
	new_str[j] = '\0';
	free(tmp_token->value);
	tmp_token->value = new_str;
	// new_str = NULL;
	// free(new_str);
}

void	append_str(char **new, char *token, int start, int i, int *j)
{
	(*new) = ft_realloc(*new, *j + 1, ((*j) + i - start) + 1);
	while (start < i)
	{
		(*new)[*j] = token[start];
		start++;
		(*j)++;
	}
}
