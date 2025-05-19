/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:35:32 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/19 09:49:53 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*check_dollar(char *value, t_shell *mini)
{
	char	*str;

	if ((ft_strcmp(value, "$") == 0) && mini->shel_pid)
	{
		str = ft_itoa(mini->shel_pid);
		return (str);
	}
	return (NULL);
}
