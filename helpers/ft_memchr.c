/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:24:31 by motelti           #+#    #+#             */
/*   Updated: 2024/11/06 15:07:59 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *) s;
	ch = (unsigned char) c;
	while (n--)
	{
		if (*p == ch)
			return ((void *) p);
		p++;
	}
	return (NULL);
}
