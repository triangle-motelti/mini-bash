/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:39:46 by motelti           #+#    #+#             */
/*   Updated: 2024/11/11 19:40:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_s;
	size_t	len_d;
	size_t	i;

	len_s = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (len_s);
	len_d = ft_strlen(dst);
	i = 0;
	if (dstsize <= len_d)
		return (len_s + dstsize);
	while (src[i] && (len_d + i < dstsize - 1))
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}
