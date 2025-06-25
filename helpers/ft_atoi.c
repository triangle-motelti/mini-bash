/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:20:00 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/25 19:00:03 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_isspace(int c)
{
	if (c == 32)
		return (1);
	return (0);
}

int	ft_atol(const char *p, long *result)
{
	int		i;
	int		sign;
	long	r;

	i = 0;
	sign = 1;
	r = 0;
	while (ft_isspace(p[i]))
		i++;
	if (p[i] == '-')
		sign = -1;
	i += (p[i] == '+' || p[i] == '-');
	if (!ft_isdigit(p[i]))
		return (1);
	while (ft_isdigit(p[i]))
	{
		if (r > LONG_MAX / 10
			|| (r == LONG_MAX / 10 && (p[i] - '0') > LONG_MAX % 10))
			return (1);
		r = r * 10 + (p[i] - '0');
		i++;
	}
	if (p[i] && ft_isascii(p[i]))
		return (1);
	return (*result = r * sign, 0);
}

static int	overflow(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;
	unsigned long	max;

	result = 0;
	sign = 1;
	max = 9223372036854775807;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (max - (*str - '0')) / 10)
			return (overflow(sign));
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
