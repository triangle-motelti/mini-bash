/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:50:30 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/13 21:29:28 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0 && s[len] != (char)c)
		len--;
	if (s[len] == (char)c)
		return ((char *)(s + len));
	return (0);
}

int	ft_strrchr_advance(char *s, char *str_to_find)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = -1;
	if (!s || !str_to_find)
		return (-1);
	while (str_to_find[j])
	{
		if (s[i] == str_to_find[j])
		{
			if (i == 0)
				start = j;
			i++;
			if (s[i] == '\0' && str_to_find[i] == '\0')
				return (start);
		}
		j++;
	}
	return (-1);
}
