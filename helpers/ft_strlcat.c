/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:52:29 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/21 09:51:09 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			len;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (dstsize <= len)
		return (dstsize + ft_strlen(src));
	while (dstsize - 1 - len > i && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + ft_strlen(src));
}
