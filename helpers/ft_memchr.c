/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:15:55 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/21 09:59:43 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pt;

	pt = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (pt[i] == (unsigned char)c)
			return ((void *)(pt + i));
		i++;
	}
	return (NULL);
}
