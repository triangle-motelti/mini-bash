/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:42:11 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/21 11:51:54 by aamraouy         ###   ########.fr       */
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

int	ft_strchr_sp(char *value, t_token *tkn)
{
	int		i;
	char	quote;

	i = 0;
	tkn->spaces = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
		{
			quote = value[i];
			i++;
			while (value[i] && value[i] != quote)
				i++;
		}
		else if (value[i] == ' ')
			tkn->spaces++;
		if (value[i])
			i++;
	}
	return (tkn->spaces);
}
