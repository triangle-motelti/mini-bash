/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:07:53 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/06 13:11:50 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*mal;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	mal = malloc(count * size);
	if (!mal)
		return (NULL);
	ft_bzero (mal, count * size);
	return (mal);
}
