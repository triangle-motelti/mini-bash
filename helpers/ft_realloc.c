/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:54:12 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/08 18:54:39 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*n_ptr;
	size_t	copy_size;

	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	if (old_size == new_size)
		return (ptr);
	n_ptr = malloc(new_size);
	if (!n_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(n_ptr, ptr, copy_size);
		free(ptr);
	}
	return (n_ptr);
}
