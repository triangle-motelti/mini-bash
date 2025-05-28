/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:41 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 14:25:03 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *alloc, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (i < len1)
	{
		alloc[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		alloc[i + j] = s2[j];
		j++;
	}
	alloc[i + j] = '\0';
	return (alloc);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*pt;
	size_t	space;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	space = ft_strlen(s1) + ft_strlen(s2);
	pt = (char *)malloc(space + 1);
	if (!pt)
		return (NULL);
	return (join(pt, s1, s2));
}
