/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:05:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/17 21:04:08 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
// #include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
typedef struct	s_env
{
	char		*value;
	struct s_env	*next_pt;
} t_env;

typedef struct	s_minishell 
{
	t_env	*env;
	char	*line;

}	t_shell;

#endif
