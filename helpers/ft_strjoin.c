/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:10:17 by motelti           #+#    #+#             */
/*   Updated: 2024/11/11 19:11:12 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	arr = malloc(((len_s1 + len_s2) + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (s1[i])
		arr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		arr[j++] = s2[i++];
	arr[j] = 0;
	return (arr);
}
