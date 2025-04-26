/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:48:56 by aamraouy          #+#    #+#             */
/*   Updated: 2024/11/06 13:13:13 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	is_digit;
	int	is_alpha;

	is_digit = ft_isdigit(c);
	is_alpha = ft_isalpha(c);
	if (is_digit)
		return (c);
	else if (is_alpha)
		return (c);
	return (0);
}
