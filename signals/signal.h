
#ifndef SIGNAL_H
#define SIGNAL_H

#include "../minishell.h"

extern volatile sig_atomic_t g_received_signal;

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	setup_signals(void);

#endif
