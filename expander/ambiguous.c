/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:54 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/20 10:59:16 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	ambiguous_case(t_token *tokens, t_shell *mini)
{
	char	**split;
	int		count;
	(void)mini;
	if (!tokens->value)
	{
		tokens->ambiguous = 1;
		return ;
	}
	if (tokens->quote == NQUOTE)
	{
		split = ft_split(tokens->value, ' ');
		if (!split)
			return ;
		count = 0;
		while (split[count])
			count++;
		if (count != 1)
			tokens->ambiguous = 1;
		free_args(split);
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
			i = start;
			while (value[i])
			{
				if (value[i] == ' ')
				{
					str = ft_substr(value, start, i - start);
					if (ft_strcmp(str, env->value) == 0)
					{
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
