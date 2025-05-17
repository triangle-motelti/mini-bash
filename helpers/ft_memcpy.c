/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:28:18 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/13 10:38:51 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	char		*sr;
	size_t		i;

	dest = (char *)dst;
	sr = (char *)src;
	if (dest == sr)
		return (dst);
	i = 0;
	while (i < n)
	{
		dest[i] = sr[i];
		i++;
	}
	return (dst);
}
