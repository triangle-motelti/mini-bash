/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:42:02 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/13 19:12:40 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	i;
	size_t	words;
	int		index;

	i = 0;
	words = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] != c && index == 0)
		{
			index = 1;
			words++;
		}
		else if (s[i] == c)
			index = 0;
		i++;
	}
	return (words);
}

static char	*fill_with_words(char const *s, char c)
{
	char	*mem_fill;
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	mem_fill = (char *)malloc(i + 1);
	if (!mem_fill)
		return (NULL);
	ft_strlcpy(mem_fill, s, i + 1);
	return (mem_fill);
}

static int	free_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != NULL)
			free(s[i]);
		i++;
	}
	free(s);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**lst;
	size_t		i;
	size_t		j;

	if (!s && !s[0])
		return (NULL);
	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < ft_countword(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		lst[j] = fill_with_words(s + i, c);
		if (!lst[j] && free_array(lst))
			return (NULL);
		i += ft_strlen(lst[j]);
		j++;
	}
	lst[j] = NULL;
	return (lst);
}
