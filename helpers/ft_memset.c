/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:38:37 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/21 09:41:43 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = str;
	while (size)
	{
		ptr[i] = (unsigned char )c;
		i++;
		size--;
	}
	return (str);
}
