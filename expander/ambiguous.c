/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:41:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/26 14:02:02 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	ambiguous_case(t_token *tokens, t_shell *mini)
{
	char	**split;
	int		count;

	(void)mini;
	if (!tokens->value)
	{
		tokens->ambiguous = 1;
		return ;
	}
	if (tokens->quote == NQUOTE)
	{
		split = ft_split(tokens->value, ' ');
		if (!split)
			return ;
		count = 0;
		while (split[count])
			count++;
		if (count != 1)
			tokens->ambiguous = 1;
		free_args(split);
	}
}

t_bool	standard_case(t_shell *shll)
{
	int		i;
	t_token	*tkn;

	i = 0;
	tkn = shll->tokens;
	if (tkn->standard_case == 1)
	{
		while (tkn)
		{
			if (ft_strcmp(tkn->value, "export") != 0)
			{
				while (tkn->value[i])
				{
					if (tkn->value[i] == '=')
						return (TRUE);
					if (tkn->value[i] == ' ')
						return (FALSE);
					i++;
				}
			}
			tkn = tkn->next;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool	has_complement(char *value, int i)
{
	char	quote;

	quote = value[i];
	i++;
	while (value[i] && value[i] != quote)
		i++;
	if (value[i] == quote)
		return (TRUE);
	else
		return (FALSE);
}

long	herdoc_count(t_token *tokens)
{
	t_token	*tkn;
	long	count;

	tkn = tokens;
	count = 0;
	while (tkn)
	{
		if (ft_strcmp(tkn->value, "<<") == 0)
			count++;
		tkn = tkn->next;
	}
	return (count);
}
