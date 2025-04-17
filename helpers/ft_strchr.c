/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:35:07 by motelti           #+#    #+#             */
/*   Updated: 2024/11/11 19:17:30 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	s1;
	char	*s2;
	int		i;

	i = 0;
	s2 = (char *) s;
	s1 = (char)c;
	while (s2[i] != s1)
	{
		if (s2[i] == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return (s2 + i);
}
