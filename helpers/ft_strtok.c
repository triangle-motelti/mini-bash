/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:00:57 by motelti           #+#    #+#             */
/*   Updated: 2025/04/20 17:43:36 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next;
	char		*start;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);
	while (*next && ft_strchr(delim, *next))
		next++;
	if (*next == '\0')
		return (NULL);
	start = next;
	while (*next && !ft_strchr(delim, *next))
		next++;
	if (*next)
	{
		*next = '\0';
		next++;
	}
	else
		next = NULL;
	return (start);
}
