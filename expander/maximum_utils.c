/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maximum_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:34:50 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/08 08:58:32 by kali             ###   ########.fr       */
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

t_bool	standard_case(t_shell *shll)
{
	if (ft_strcmp(shll->tkn->value, "export") == 0)
		return (TRUE);
	return (FALSE);
}

size_t	ft_count_words(t_token *tkn, char delim)
{
	char	*s;
	int		flag;
	size_t	cnt;
	int		i;
	char	quote;

	s = tkn->value;
	cnt = 0;
	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
		   quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] && s[i] == quote)
				i++;
			cnt++;
			flag = 0;
		}
		else if (s[i] == delim)
		{
			flag = 0;
			i++;
		}
		else if (s[i] != delim && flag == 0)
		{
			flag = 1;
			cnt++;
			i++;
		}
		else
			i++;
	}
	return cnt;
}

char	**advanced_split(t_token *tkn, char delim)
{
	char	*s;
	size_t	words;
	char	**list;
	size_t	w;
	int		i;
	int		start;
	char	quote;

	words = ft_count_words(tkn, delim);
	w = 0;
	i = 0;
	s = tkn->value;
	// printf("there are %ld words out there \n", words);
	list = malloc((words + 1) * sizeof(char *));
	if (!list)
		return NULL;
	while (w < words)
	{
		// while (s[i] && s[i] == delim && !inside_quote(s, i))
		// 	i++;
		while (s[i] && s[i] == delim)
			i++;
		start = i;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] && s[i] == quote)
				i++;
		}
		else //not a delim and not a quote;
		{
			while (s[i] && s[i] != delim && (s[i] != '\'' && s[i] != '"'))
				i++;
			// while (s[i] && !(!inside_quote(s, i) && s[i] == delim))
			// 	i++; 
		}
		list[w++] = ft_substr(s, start, i - start);
		if (!list[w-1])
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
