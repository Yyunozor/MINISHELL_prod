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

#include <signal.h>
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

void	signals_set_interactive(void)
{
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}
