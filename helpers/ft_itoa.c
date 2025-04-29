/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:01:51 by motelti           #+#    #+#             */
/*   Updated: 2024/11/07 01:43:16 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ln(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static char	*fill(char *tmp, long nbr)
{
	int	i;
	int	len;

	len = ln(nbr);
	if (nbr == 0)
		tmp[0] = '0';
	else if (nbr < 0)
	{
		nbr *= -1;
		tmp[0] = '-';
	}
	i = len - 1;
	while (nbr > 0)
	{
		tmp[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	return (tmp);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*arr;
	long	nb;

	l = ln(n);
	nb = n;
	arr = malloc((l + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	arr[l] = '\0';
	return (fill(arr, nb));
}
