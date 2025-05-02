/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:24:29 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/27 12:36:57 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_args(int ac)
{
	if (ac != 1)
		exit_error("arguments not allowed : syntax { ./minishell }\n");
}

void exit_error(const char *msg)
{
	perror(msg);
	//implement a signal handling to bach again into the first stat
	// exit(1);
}
