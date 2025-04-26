/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:24:29 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/18 16:35:06 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_args(int ac)
{
	if (ac != 1)
		exit_error("arguments not allowed : syntax { ./minishell }\n");
}