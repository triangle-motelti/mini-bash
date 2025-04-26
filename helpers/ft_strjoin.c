/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:41 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/17 15:49:10 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *alloc, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		alloc[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		alloc[i + j] = s2[j];
		j++;
	}
	alloc[i + j] = '\0';
	return (alloc);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	int		space;
	int		i;
	int		ind;

	i = 0;
	ind = 0;
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
