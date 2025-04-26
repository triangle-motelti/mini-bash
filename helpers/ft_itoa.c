/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:44:40 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/21 09:57:52 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*zero_case(char *res)
{
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	long	nbr;

	i = count_digit(n);
	nbr = (long)n;
	result = (char *)malloc(i + 1);
	if (!result)
		return (NULL);
	if (n == 0)
		return (zero_case(result));
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	result[i] = '\0';
	while (nbr)
	{
		result[--i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}
