/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:26:12 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/21 10:03:21 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*sr;

	dest = (char *)dst;
	sr = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (dest <= sr)
		return (ft_memcpy(dst, src, n));
	else
	{
		dest += n;
		sr += n;
		while (n--)
			*(--dest) = *(--sr);
	}
	return (dst);
}
