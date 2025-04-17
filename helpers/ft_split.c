/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:07:37 by motelti           #+#    #+#             */
/*   Updated: 2024/11/10 22:50:59 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_free_array(char **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
	return (NULL);
}

static char	**ft_fill_array(char **array, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		word_index;

	i = 0;
	word_index = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		array[word_index] = ft_substr(s, j, i - j);
		if (!array[word_index])
			return (ft_free_array(array, word_index - 1));
		word_index++;
	}
	array[word_index] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (NULL);
	if (!ft_fill_array(array, s, c))
		return (NULL);
	return (array);
}
