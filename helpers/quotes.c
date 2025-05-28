/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:17:22 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 14:24:15 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_peer(char *input, char quote, int *i)
{
	while (input[*i])
	{
		if (input[*i] == quote)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

char	quotes_syntax(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			if (find_peer(input, quote, &i))
				continue ;
			else
				return ('n');
		}
		else
			i++;
	}
	return ('v');
}
