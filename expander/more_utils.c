/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:35:32 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/15 09:39:24 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*check_dollar(char *value, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if ((ft_strcmp(value, "$") == 0) && (ft_strcmp(tmp->key, "MANAGERPID") == 0))
			return (tmp->value);
		tmp = tmp->next_pt;
	}
	return (NULL);
}
