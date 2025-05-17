/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:29:54 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/17 11:15:42 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_separator(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>')|| (input[i] == '<' && input[i + 1] == '<'))
		return (2);
	else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		return (1);
	else
		return (0);
}

int	is_wspace(char input)
{
	if ((input >= 9 && input <= 13 )| (input == 32))
		return (1);
	return (0);
}

void	keep_tracking(t_shell *mini, int j, int start, char *input)
{
	char	*word;
	char	c;
	int		i;
	int		k;

	word = malloc(j - start + 1);
	if (!word)
		return ;
	i = start;
	k = 0;
	while (i < j)
	{
		c = input[i];
		word[k] = c;
		k++;
		i++;
	}
	word[k] = '\0';
	add_token(mini, word, WORD);
}
