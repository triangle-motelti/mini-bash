/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:35:58 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/28 18:24:28 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_word(t_shell *mini, char *input, int i)
{
	int		start;
	int		track;
	char	quote;

	track = i;
	start = i;
	while (input[track] != '\0' && !is_wspace(input[track])
		&& !is_separator(input, track))
	{
		quote = input[track];
		if (quote == '\'')
		{
			if (!more_quote_handling(input, &track, 1))
				return (mini->exit_status = 2, 0);
		}
		else if (quote == '"')
		{
			if (!more_quote_handling(input, &track, 2))
				return (mini->exit_status = 2, 0);
		}
		else
			track++;
	}
	keep_tracking(mini, track, start, input);
	return (track);
}

int	set_separator(char *c, int i)
{
	if (is_wspace(c[i]))
		return (SPACES);
	if (c[i] == '>' && c[i + 1] == '>')
		return (APPEND);
	if (c[i] == '<' && c[i + 1] == '<')
		return (HEREDOC);
	if (c[i] == '|')
		return (PIPE);
	if (c[i] == '>')
		return (TRUNC);
	if (c[i] == '<')
		return (INPUT);
	if (c[i] == '\0')
		return (END);
	else
		return (0);
}

int	handle_quotes(t_shell *mini, char *input, int *i, int start)
{
	char	quote;

	start = (*i);
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] != quote)
			{
				printf("missing closing quote `%c'\n", quote);
				return (0);
			}
			(*i)++;
		}
		else if (!is_wspace(input[*i]) && !is_separator(input, *i))
			(*i)++;
		else
			break ;
	}
	keep_tracking(mini, *i, start, input);
	return (1);
}

void	sep_handling(t_shell *mini, char *input, int *i)
{
	int		len;
	int		type;
	char	*sep;

	len = is_separator(input, *i);
	sep = ft_substr(input, *i, len);
	type = set_separator(input, *i);
	add_token(mini, sep, type);
	(*i) += len;
}

t_bool	tokenizer(t_shell *mini, char *input, int i, int len)
{
	int		sep;

	while (i < len)
	{
		if (is_wspace(input[i]))
		{
			i++;
			continue ;
		}
		sep = is_separator(input, i);
		if (sep != 0)
			sep_handling(mini, input, &i);
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!handle_quotes(mini, input, &i, 0))
				return (mini->exit_status = 2, FALSE);
		}
		else
		{
			i = handle_word(mini, input, i);
			if (i == 0)
				return (FALSE);
		}
	}
	return (TRUE);
}
