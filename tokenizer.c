/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:35:58 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/26 10:03:20 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_shell *mini, char *sep, int type)
{
	t_token	*new;//this tlist needs to be t_token

	if (!sep)
		return ;
	new = ft_lstnew(sep, type);
	if (!new)
		return ;
	ft_lstadd_back(&mini->tokens, new);
}
int	handle_word(t_shell *mini, char *input, int i)
{
	int start;
	int	track;
	char	quote;

	track = i;
	start = i;
	while ((quote = input[track]) != '\0' && !is_wspace(input[track]) && !is_separator(input, track))
	{
		if (quote == '\'')
		{
			track++;
			while (input[track] && input[track] != '\'')
				track++;
			if (input[track] != '\'')
			{
				printf("syntax error: unclosed quotes\n");
				return (0);
			}
			track++;
		}
		else if(quote == '"')
		{
			track++;
			while (input[track] && input[track] != '"')
				track++;
			if (input[track] != '"')
			{
				printf("syntax error: unclosed quotes\n");
				return (0);
			}
			track++;
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

int	handle_quotes(t_shell *mini, char *input, int *i)
{
	char	quote;
	int		start;
	char	*word;

	quote = input[*i];
	(*i)++;
	start = (*i);
	while(input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i]  != quote)
	{
		printf("lexer error : missing closing quote\n");
		return (0);
	}
	word = ft_substr(input, start ,(*i) - start);
	add_token(mini, word, WORD);
	// free(word);
	(*i)++;
	return (1);
}

void	sep_handling(t_shell *mini, char *input, int *i)
{
	int	len;
	int	type;
	char	*sep;

	len = is_separator(input, *i);
	sep = ft_substr(input, *i, len);
	type = set_separator(input, *i);
	add_token(mini, sep, type);
	// free(sep);
	(*i) += len;
}

t_bool	tokenizer(t_shell *mini, char *input, int i)
{
	int		len;
	int		count = 0;
	char	quote;
	int		sep;

	len = ft_strlen(input);
	while (i < len)
	{
		if (is_wspace(input[i]))
		{
			i++;
			continue;
		}
		sep = is_separator(input, i);
		if (sep != 0)
			sep_handling(mini, input, &i);
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!handle_quotes(mini, input, &i))
				return (FALSE);
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
