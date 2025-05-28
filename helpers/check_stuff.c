/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:24:29 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/28 12:19:52 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_args(int ac)
{
	if (ac != 1)
		exit_error("arguments not allowed : syntax { ./minishell }\n");
}

void	exit_error(const char *msg)
{
	perror(msg);
}
