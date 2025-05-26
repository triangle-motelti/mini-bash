/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:35:32 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/26 12:18:48 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// char	*check_dollar(char *value, t_shell *mini)
// {
// 	char	str[2];
// 	char	*ds;

// 	(void)mini;
// 	if ((ft_strcmp(value, "$") == 0))
// 	{
// 		// str = ft_itoa(mini->shel_pid);
// 		ds = ft_strcpy(str, "$");
// 		return (ds);
// 	}
// 	return (NULL);
// }

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
	int	i;
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

// char	*check_for_limiters(char *value, int *i)
// {
// 	char	*extracted_value;
// 	int		k;

// 	k = 0;
// 	extracted_value = malloc(ft_strlen(value) + 1);
// 	while (value[*i])
// 	{
// 		if (is_limiter_expanders(value, *i) == FALSE)
// 		{
// 			if (*i >= 1 && value[*i] == '$' && value[*i - 1] == '$')
// 				extracted_value[k++] = value[(*i)++];
// 			break ;
// 		}
// 		extracted_value[k++] = value[(*i)++];
// 	}
// 	extracted_value[k] = '\0';
// 	return (extracted_value);
// }
