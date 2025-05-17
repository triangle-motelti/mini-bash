/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:54 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/17 18:04:59 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	ambiguous_case(t_token *tokens, t_shell *mini)
{
	t_env	*tmp_env;
	int		i;

	tmp_env = mini->env;
	i = 0;
	while (tmp_env)
	{		
		if (ft_strchr(tokens->value, ' ') != NULL)
		{
			i = ft_strrchr_advance(tokens->value, tmp_env->value);
			if (i != -1)
				tokens->ambiguous = 1;
		}
		tmp_env = tmp_env->next_pt;
	}
}

int	check_environements(char *value, t_shell *mini)
{
	t_env	*env;
	int		i;
	int		start;
	char	*str;

	env = mini->env;
	start = -1;
	while (env)
	{
		start = ft_strrchr_advance(value, env->value);
		if (start != -1)
		{
			// printf("environement is %s\n", env->value);
			i = start;
			while (value[i])
			{
				if (value[i] == ' ')
				{
					str = ft_substr(value, start, i - start);
					if (ft_strcmp(str, env->value) == 0)
					{
						printf("--------------envir is : %s, substracted value is %s, value is :%s\n", env->value, str, value);
						free(str);
						return (0);
					}
					free(str);
					return (i);
				}
				i++;
			}
			return (0);
		}
		env = env->next_pt;
	}
	return (0);
}
