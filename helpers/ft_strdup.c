/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:27:17 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/11 13:07:18 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*mem;
	int		i;

	i = 0;
	mem = (char *)malloc(ft_strlen(s1) + 1);
	if (!mem)
		return (NULL);
	while (*s1)
	{
		mem[i] = *s1;
		s1++;
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
