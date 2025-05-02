/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:43:16 by motelti           #+#    #+#             */
/*   Updated: 2025/05/02 14:43:29 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_sep(const char *s1, const char *s2, const char *sep)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len_sep;

	if (!s1 || !s2 || !sep)
		return (NULL);
	len1 = ft_strlen(s1);
	len_sep = strlen(sep);
	len2 = strlen(s2);
	result = malloc(len1 + len_sep + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, sep, len_sep);
	ft_memcpy(result + len1 + len_sep, s2, len2);
	result[len1 + len_sep + len2] = '\0';
	return (result);
}
