/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/06 13:40:16 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "../minishell.h"

t_bool	standard_case(t_shell *shll);

char	**advanced_split(t_token *tkn, char delim);;
char	*norm_for_dollar_hand(char *value, t_shell *mini);
// int	    check_environements(char *value, t_shell *mini, t_token *token);
// char	*check_dollar(char *value, t_shell *mini);
void	append_character(char **new, int *i, char c);
char	*handle_dollar(char *new, char *value, t_shell *mini);
t_bool	dollar_expansion(char *token, t_shell *mini, char **new, int cap);
t_bool	expander(t_shell *mini);
// void	copy_env(t_shell *mini, char **env, int i);
void	ambiguous_case(t_token *tokens, t_shell *mini);
void	fill_splited(char **splited, t_token *token);
// char	*check_for_limiters(char *value, int *i);
void	invalid_or_not_expanded(char *newvalue, t_token *token);
void	single_quote(char *token, char **new, t_shell *mini);
char	*get_env_value(char *value, t_shell *mini);
t_env	*build_env_list(t_shell *shell, char **envp);
void	split_in_case(t_token *token, t_shell *mini);
t_bool	is_limiter_expanders(char *value, int i);
void	rm_quotes(t_token *token);
void	append_str(char **new, char *token, int start, t_shell *mini);
char	*expand_each_token(char *token, int i, int j, t_shell *mini);

#endif
