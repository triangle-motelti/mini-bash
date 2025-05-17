/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:21:10 by motelti           #+#    #+#             */
/*   Updated: 2025/05/13 10:39:09 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str) && !(*str == '-' || *str == '+'))
			return (0);
		str++;
	}
	return (1);
}
