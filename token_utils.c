/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:29:54 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/26 10:04:00 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (input >= 9 && input <= 13 | input == 32)
		return (1);
	return (0);
}

void	keep_tracking(t_shell *mini, int j, int start, char *input)
{
	char	*word;
	char	c;
	int		i;
	int		k;

	word = malloc((j - start) + 1);
	if (!word)
		return ;
	i = start;
	k = 0;
	while (i < j)
	{
		c = input[i];
		if (c == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
			{
				word[k++] = input[i];
				i++;
			}
			if (i < j && input[i] != '\'')
				i++;
		}
		else if(c == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
			{
				word[k++] = input[i];
				i++;
			}
			if (i < j && input[i] != '\'')
				i++;
		}
		else
		{
			word[k++] = c;
			i++;
		}
	}
	word[k] = '\0';
	add_token(mini, word, WORD);
	// free(word);
}
