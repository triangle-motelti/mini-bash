/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:48:10 by motelti           #+#    #+#             */
/*   Updated: 2025/04/27 22:25:58 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// char	**parse_input(const char *input)
// {
// 	char	**args;
// 	char	*input_copy;
// 	char	*token;
// 	int		count;
// 	int		i;
// 	size_t	len; 

// 	i = 0;
// 	count = 0;
// 	input_copy = ft_strdup(input);
// 	if (!input_copy)
// 		return (NULL);
// 	token = ft_strtok(input_copy, " \t\n");
// 	while (token)
// 	{
// 		count++;
// 		token = ft_strtok(NULL, " \t\n");
// 	}
// 	free(input_copy);
// 	args = malloc((count + 1) * sizeof(char *));
// 	if (!args)
// 		return (NULL);
// 	input_copy = ft_strdup(input);
// 	if (!input_copy)
// 		return (free(args), NULL);
// 	token = ft_strtok(input_copy, " \t\n");
// 	while (token && i < count)
// 	{
// 		len = strlen(token);
// 		if ((token[0] == '"' && token[len - 1] == '"') ||
// 			(token[0] == '\'' && token[len - 1] == '\''))
// 		{
// 			token[len - 1] = '\0';
// 			args[i++] = ft_strdup(token + 1);
// 		}
// 		else
// 			args[i++] = ft_strdup(token);
// 		token = ft_strtok(NULL, " \t\n");
// 	}
// 	args[i] = NULL;
// 	free(input_copy);
// 	return (args);
// }

static int	count_tokens_quote(const char *input)
{
	int			count;
	const char	*s;

	count = 0;
	s = input;
	while (*s)
	{
		skip_ws(&s);
		if (!*s)
			break ;
		count++;
		if (*s == '"' || *s == '\'')
			skip_quoted(&s);
		else
			skip_unquoted(&s);
	}
	return (count);
}

static char	*extract_token(const char **sp)
{
	if (**sp == '"' || **sp == '\'')
		return (extract_quoted(sp));
	else
		return (extract_unquoted(sp));
}

char **parse_input(t_shell *shell, const char *input)
{
	char		**args;
	const char	*s;
	int			count;
	int			i;
	char		*tok;

	s = input;
	i = 0;
	count = count_tokens_quote(input);
	args  = malloc((count + 1) * sizeof(*args));
	if (!args)
		return (NULL);
	while (*s)
	{
		skip_ws(&s);
		if (!*s)
			break;
		if (*s == '"' || *s == '\'')
		{
			tok = extract_quoted(&s);
			if (!tok)
				return (NULL);
		}
		else
			tok = extract_unquoted(&s);
		args[i++] = tok;
	}
	return (args[i] = NULL, args);
}
