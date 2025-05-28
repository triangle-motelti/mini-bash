/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maximum_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:34:50 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 18:42:00 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*norm_for_dollar_hand(char *value, t_shell *mini)
{
	int		k;
	char	*extracted_val;

	extracted_val = malloc(ft_strlen(value) + 1);
	if (!extracted_val)
		return (NULL);
	k = 0;
	while (is_limiter_expanders(value, mini->i) != FALSE)
		extracted_val[k++] = value[(mini->i)++];
	extracted_val[k] = '\0';
	return (extracted_val);
}
