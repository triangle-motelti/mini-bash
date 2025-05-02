/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:30:07 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/18 11:55:08 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pt;
	size_t	i;
	size_t	src_length;

	if (!s)
		return (NULL);
	src_length = ft_strlen(s);
	if (start >= src_length)
		return (ft_strdup(""));
	if (len > src_length - start)
		i = src_length - start;
	else
		i = len;
	pt = (char *)malloc(i + 1);
	if (!pt)
		return (NULL);
	ft_strlcpy(pt, s + start, i + 1);
	return (pt);
}
