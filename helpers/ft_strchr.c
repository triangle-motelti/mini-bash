/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:42:11 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/26 14:42:13 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	char	*str;

	str = s;
	while (*str != '\0' && *str != (char)c)
		str++;
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}
