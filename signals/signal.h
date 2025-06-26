/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:08:46 by motelti           #+#    #+#             */
/*   Updated: 2025/06/24 11:01:34 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"

extern volatile sig_atomic_t	g_received_signal;

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	setup_signals(void);

#endif
