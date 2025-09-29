/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 01:20:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/29 07:21:50 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

#include <readline/readline.h>
#include <unistd.h>

#ifdef rl_replace_line

static void	clear_prompt_line(void)
{
	rl_replace_line("", 0);
}

#else

static void	clear_prompt_line(void)
{
}

#endif

static void	sigint_prompt(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	clear_prompt_line();
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
	sigaction(SIGQUIT, &sa, NULL);
}
