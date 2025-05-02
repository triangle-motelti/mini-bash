/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:04:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/01 12:56:11 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*fill_command(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->flag == WORD && tmp->status == DEFAULT)// I NEED to set this in tokenization
	{
		//check the value if it contains whitespaces, 
	}
	
}

// void	handle_files(t_commands *cmds, t_token *token)
// {
// 	if (token->flag = INPUT)
// 		cmds->fd_in = 1;
// 	else if (token->flag = TRUNC)
// 		cmds->fd_out = 1;
// }
