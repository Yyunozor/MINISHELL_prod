/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 00:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/25 11:47:00 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t g_signal_state = 0;

/* SIGINT handler in prompt mode: record status and flag, print newline */
static void	h_sigint_prompt(int sig)
{
	(void)sig;
	g_signal_state = 130 | 0x10000; // status=130, flag=1
	write(1, "\n", 1);
}

/* SIGQUIT handler in prompt mode: ignored intentionally */
static void	h_sigquit_prompt(int sig)
{
	(void)sig;
}

void	set_prompt_signals(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = h_sigint_prompt;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = h_sigquit_prompt;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_exec_signals_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_exec_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	update_status_from_wait(int status)
{
	if (WIFEXITED(status))
		g_signal_state = (g_signal_state & 0x10000) | WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(1, "\n", 1);
		g_signal_state = (g_signal_state & 0x10000) | (128 + sig);
	}
}
