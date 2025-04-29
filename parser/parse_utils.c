/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:18:25 by motelti           #+#    #+#             */
/*   Updated: 2025/04/25 18:08:00 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*extract_unquoted(const char **sp)
{
	const char	*start;
	char		*token;
	size_t		len;

	start = *sp;
	while (**sp && **sp != ' ' && **sp != '\t' && **sp != '\n')
		(*sp)++;
	len = *sp - start;
	token = ft_substr(start, 0, len);
	if (!token)
		return (NULL);
	return (token);
}

char *extract_quoted(const char **sp)
{
	const char	*start;
	char		q;
	size_t		len;
	char		*tok;

	q = **sp;
	(*sp)++;
	start = *sp;
	while (**sp && **sp != q)
		(*sp)++;
	if (**sp != q)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", STDERR_FILENO);
		ft_putchar_fd(q, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		// mini->exit_status = 126;
		exit(126);
		return (NULL);
	}
	len = *sp - start;
	tok = ft_substr(start, 0, len);
	(*sp)++;
	return (tok);
}

void	skip_ws(const char **s)
{
	while (**s == ' ' || **s == '\t' || **s == '\n')
		(*s)++;
}

int skip_quoted(const char **s)
{
	char	q;

	q = **s;
	(*s)++;
	while (**s && **s != q)
		(*s)++;
	if (**s == q)
	{
		(*s)++;
		return (0);
	}
	return (-1);
}

void	skip_unquoted(const char **s)
{
	while (**s && **s != ' ' && **s != '\t' && **s != '\n')
		(*s)++;
}
