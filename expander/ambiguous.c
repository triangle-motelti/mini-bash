/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:41:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/21 11:52:31 by aamraouy         ###   ########.fr       */
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
	if (shll->tokens->standard_case == 1)
		return (TRUE);
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
