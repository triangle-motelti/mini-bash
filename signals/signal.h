/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:08:46 by motelti           #+#    #+#             */
/*   Updated: 2025/05/28 15:10:31 by motelti          ###   ########.fr       */
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
