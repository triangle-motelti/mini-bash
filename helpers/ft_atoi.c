/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:33:54 by motelti           #+#    #+#             */
/*   Updated: 2024/11/12 15:18:52 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(const char *s, int size, int sign)
{
	while (*s == 48)
	{
		s++;
		size--;
	}
	if (size > 19)
		return (0);
	if (size < 19)
		return (1);
	if (ft_strncmp(s, "9223372036854775807", size) > 0 && sign)
		return (0);
	if (ft_strncmp(s, "9223372036854775808", size) > 0 && sign == -1)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	const char	*s1;
	long		r;
	int			s;

	r = 0;
	s = 1;
	while (*str && ((*str >= 9 && 13 >= *str) || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			s *= -1;
	}
	s1 = str;
	while (*str >= '0' && '9' >= *str)
		r = r * 10 + (*str++ - '0');
	if (!check(s1, str - s1, s))
	{
		if (s == 1)
			return (-1);
		if (s == -1)
			return (0);
	}
	return (r * s);
}
