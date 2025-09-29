/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 01:20:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 09:16:25 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

#include <readline/readline.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_received = 0;

static void	sigint_prompt(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	#ifdef rl_replace_line
	rl_replace_line("", 0);
	#endif
	rl_redisplay();
}

static void	sigquit_prompt(int sig)
{
	(void)sig;
}

void	signals_set_interactive(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_prompt;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = sigquit_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signals_set_exec_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_set_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	sigint_heredoc(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	#ifdef rl_replace_line
	rl_replace_line("", 0);
	#endif
}

void	signals_set_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}