/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:41:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/26 14:41:49 by aamraouy         ###   ########.fr       */
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

// int	norm_for_check_environements(char *value, int i, int start, char *env_value, int quote)
// {
// 	char	*str;

// 	if (quote == QUOTE)
// 		return (0);
// 	while (value[i])
// 	{
// 		if (value[i] == ' ')
// 		{
// 			str = ft_substr(value, start, i - start);
// 			if (ft_strcmp(str, env_value) == 0)
// 			{
// 				free(str);
// 				return (0);
// 			}
// 			free(str);
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	check_environements(char *value, t_shell *mini, t_token *token)
// {
// 	t_env	*env;
// 	int		i;
// 	int		start;
// 	// char	*str;

// 	env = mini->env;
// 	start = -1;
// 	while (env)
// 	{
// 		start = ft_strrchr_advance(value, env->value);
// 		if (start != -1)
// 		{
// 			i = start;
// 			i = norm_for_check_environements(value, i, start, env->value, token->quote);
// 			if (i)
// 				return (i);
// 			// while (value[i])
// 			// {
// 			// 	if (value[i] == ' ')
// 			// 	{
// 			// 		str = ft_substr(value, start, i - start);
// 			// 		if (ft_strcmp(str, env->value) == 0)
// 			// 		{
// 			// 			free(str);
// 			// 			return (0);
// 			// 		}
// 			// 		free(str);
// 			// 		return (i);
// 			// 	}
// 			// 	i++;
// 			// }
// 			return (0);
// 		}
// 		env = env->next_pt;
// 	}
// 	return (0);
// }
