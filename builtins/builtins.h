/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:48:11 by motelti           #+#    #+#             */
/*   Updated: 2025/06/17 16:41:39 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

typedef struct s_kv
{
	char	*key;
	char	*value;
	int		is_append;
}	t_kv;

int		is_builtin(char *cmd);

void	echo(int ac, char **av, t_shell *shell);
int		cd(t_shell *shell, int ac, char **args);
void	pwd(t_shell *shell, int ac);
void	ft_exit(int ac, char **args, t_shell *shell);
void	ft_env(t_shell *mini, int ac, char **av);
void	unset(t_shell *mini, int ac, char **args);
void	ft_export(t_shell *mini, int ac, char **av);

void	export_ac(t_shell *shell, char **arr, int i);
t_env	*find_env_node(t_env *env, const char *key);
int		update_env_node(t_env *node, char *value);
void	sort_env(char **env_arr);

int		append_env_node(t_shell *mini, char *key, char *value);
int		is_valid_key(const char *key);

int		handle_with_equal_sign(char *arg, char *eq, t_kv *result);
int		without_equal_sign(char *arg, t_kv *kv);
int		validate_export_key(char *arg, char *key, char *value, int is_append);
int		handle_append_case(t_shell *mini, t_env *found, char *key, char *value);
int		non_append_case(t_shell *mini, t_env *found, char *key, char *value);

int		extract_key_value(char *arg, t_kv *kv);
int		update_append_env(t_shell *mini, char *key, char *value, int is_append);

#endif
