/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/20 11:05:42 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H
#include "../minishell.h"

int	check_environements(char *value, t_shell *mini);

char	*check_dollar(char *value, t_shell *mini);

t_bool	expander(t_shell *mini);
// void	copy_env(t_shell *mini, char **env, int i);
void	ambiguous_case(t_token *tokens, t_shell *mini);

void	single_quote(char *token, int *i, char **new, int *j);

char	*get_env_value(char *value, t_shell *mini);

t_env	*build_env_list(t_shell *shell, char **envp);
void	split_in_case(t_token *token, t_shell *mini);
t_bool	is_limiter_expanders(char *value, int i);
void	rm_quotes(t_token *token);
void	append_str(char **new, char *token, int start, int i, int *j);


char    *expand_each_token(char *token, int i, int j, t_shell *mini);

#endif
