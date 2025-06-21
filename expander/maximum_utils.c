/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maximum_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:34:50 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/21 11:52:07 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*norm_for_dollar_hand(char *value, t_shell *mini)
{
	int		k;
	char	*extracted_val;

	extracted_val = malloc(ft_strlen(value) + 1);
	if (!extracted_val)
		return (NULL);
	k = 0;
	while (is_limiter_expanders(value, mini->i) != FALSE)
		extracted_val[k++] = value[(mini->i)++];
	extracted_val[k] = '\0';
	return (extracted_val);
}

void	norm_optimazition(int *flag, size_t *cnt)
{
	*flag = 1;
	(*cnt)++;
}

size_t	ft_count_words(t_token *tkn, char delim, int flag, int i)
{
	size_t	cnt;
	char	quote;

	cnt = 0;
	while (tkn->value[i])
	{
		if (tkn->value[i] == '\'' || tkn->value[i] == '"')
		{
			quote = tkn->value[i];
			i++;
			while (tkn->value[i] && tkn->value[i] != quote)
				i++;
			cnt++;
			flag = 0;
		}
		else if (tkn->value[i] == delim)
			flag = 0;
		else if (tkn->value[i] != delim && flag == 0)
			norm_optimazition(&flag, &cnt);
		if (tkn->value[i])
			i++;
	}
	return (cnt);
}

char	*adv_split_normalzing(char *list, int *i, char *s)
{
	char	quote;
	int		start;

	while (s[*i] && s[*i] == ' ')
		(*i)++;
	start = *i;
	if (s[*i] == '\'' || s[*i] == '"')
	{
		quote = s[*i];
		(*i)++;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i] && s[*i] == quote)
			(*i)++;
	}
	else
	{
		while (s[*i] && s[*i] != ' ' && (s[*i] != '\'' && s[*i] != '"'))
			(*i)++;
	}
	list = ft_substr(s, start, *i - start);
	return (list);
}

char	**advanced_split(t_token *tkn, char delim, int i, size_t w)
{
	char	*s;
	size_t	words;
	char	**list;

	words = ft_count_words(tkn, delim, 0, 0);
	s = tkn->value;
	list = malloc((words + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	while (w < words)
	{
		list[w++] = adv_split_normalzing(*list, &i, s);
		if (!list[w - 1])
		{
			while (w-- > 0)
				free(list[w]);
			free(list);
			return (NULL);
		}
	}
	list[w] = NULL;
	return (list);
}
