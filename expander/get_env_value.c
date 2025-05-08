/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:52:52 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/08 18:53:06 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_env_value(char *value, t_shell *mini)
{
	t_env	*tmp_env;

	tmp_env = mini->env;
	while (tmp_env)
	{
		if (ft_strcmp(value, tmp_env->key) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next_pt;
	}
	// free(value);
	return (NULL);
}
