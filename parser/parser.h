/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:48:50 by motelti           #+#    #+#             */
/*   Updated: 2025/04/27 22:27:52 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// char	**parse_input(const char *input);
char	*extract_unquoted(const char **sp);
char	*extract_quoted(const char **sp);
void	skip_ws(const char **s);
int		skip_quoted(const char **s);
void	skip_unquoted(const char **s);

char	**parse_input(t_shell *shell, const char *input);

#endif