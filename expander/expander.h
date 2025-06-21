/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/21 11:52:41 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "../minishell.h"

t_bool	standard_case(t_shell *shll);
t_bool	has_complement(char *value, int i);

char	**advanced_split(t_token *tkn, char delim, int i, size_t w);
char	*norm_for_dollar_hand(char *value, t_shell *mini);
void	append_character(char **new, int *i, char c);
char	*handle_dollar(char *new, char *value, t_shell *mini);
t_bool	dollar_expansion(char *token, t_shell *mini, char **new, int cap);
t_bool	expander(t_shell *mini);
void	ambiguous_case(t_token *tokens, t_shell *mini);
void	fill_splited(char **splited, t_token *token);
void	invalid_or_not_expanded(char *newvalue, t_token *token);
void	single_quote(char *token, char **new, t_shell *mini);
char	*get_env_value(char *value, t_shell *mini);
void	split_in_case(t_token *token, t_shell *mini);
t_bool	is_limiter_expanders(char *value, int i);
void	rm_quotes(t_token *token);
void	append_str(char **new, char *token, int start, t_shell *mini);
char	*expand_each_token(char *token, int i, int j, t_shell *mini);

#endif
