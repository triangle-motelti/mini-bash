/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:29:54 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 20:06:37 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_separator(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
		return (2);
	else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		return (1);
	else
		return (0);
}

int	is_wspace(char input)
{
	if ((input >= 9 && input <= 13) || (input == 32))
		return (1);
	return (0);
}

void	keep_tracking(t_shell *mini, int j, int start, char *input)
{
	char	*word;

	word = ft_substr(input, start, j - start);
	add_token(mini, word, WORD);
}

void	add_token(t_shell *mini, char *sep, int type)
{
	t_token	*new;

	if (!sep)
		return ;
	new = ft_lstnew(sep, type);
	if (!new)
	{
		free(sep);
		return ;
	}
	ft_lstadd_back(&mini->tokens, new);
}

int	more_quote_handling(char *input, int *track, int sing_or_doub)
{
	if (sing_or_doub == 1)
	{
		(*track)++;
		while (input[(*track)] && input[(*track)] != '\'')
			(*track)++;
		if (input[(*track)] != '\'')
		{
			printf("mini: unexpected EOF while looking for matching `''\n");
			return (0);
		}
		(*track)++;
	}
	else if (sing_or_doub == 2)
	{
		(*track)++;
		while (input[(*track)] && input[(*track)] != '"')
			(*track)++;
		if (input[(*track)] != '"')
		{
			printf("mini: unexpected EOF while looking for matching `\"'\n");
			return (0);
		}
		(*track)++;
	}
	return (1);
}
