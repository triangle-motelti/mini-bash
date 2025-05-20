/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:35:32 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/20 11:05:25 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*check_dollar(char *value, t_shell *mini)
{
	char	*str;

	if ((ft_strcmp(value, "$") == 0) && mini->shel_pid)
	{
		str = ft_itoa(mini->shel_pid);
		return (str);
	}
	return (NULL);
}

void	single_quote(char *token, int *i, char **new, int *j)
{
	int	start;

	(*i)++;
	start = *i;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	append_str(new, token, start, *i, j);
	if (token[*i])
		(*i)++;
}
