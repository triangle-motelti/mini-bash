/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:00:40 by motelti           #+#    #+#             */
/*   Updated: 2024/11/12 23:59:00 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	m;

	x = 0;
	m = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (x < len && haystack[m])
	{
		if (haystack[m] == needle[x])
		{
			while (haystack[m + x] == needle[x] && x + m < len)
			{
				if (needle[x + 1] == '\0')
					return ((char *) &haystack[m]);
				x++;
			}
		}
		x = 0;
		m++;
	}
	return (0);
}
