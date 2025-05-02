/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:37:52 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/02 14:49:46 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

char	    *fill_command(t_token *token);
void	    flstadd_command_back(t_command **lst, t_command *new);
t_command	*new_token_node(t_token *tokens);
t_bool	    parser(t_shell *mini);
void    	keep_tracking(t_shell *mini, int j, int start, char *input);
int	        is_wspace(char input);
int		    is_separator(char *c, int i);
t_bool	    tokenizer(t_shell *mini, char *input, int i);
int	        handle_quotes(t_shell *mini, char *input, int *i);
void	    freeing_array(char **fr);
void	    add_token(t_shell *mini, char *sep, int type);
void        free_tokens(t_token *tokens);
void        free_env(t_env *env);


#endif