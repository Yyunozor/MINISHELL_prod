/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 07:41:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 17:08:36 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signals.h"
#include <signal.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <unistd.h>

static void	sigint_heredoc(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	/* Ne pas restaurer le handler - laisser le signal interrompre read() */
}

void	signals_set_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/* SIGINT : doit interrompre read() sans le redémarrer */
	sa_int.sa_handler = sigint_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;  /* Pas de SA_RESTART ! */
	sigaction(SIGINT, &sa_int, NULL);

	/* SIGQUIT : ignorer */
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
