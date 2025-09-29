/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 00:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/25 21:58:00 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

/* Exposed globals (defined in signals.c) */
extern volatile sig_atomic_t	g_sigint_flag;
extern volatile sig_atomic_t	g_last_status;

/* Prompt mode (interactive) handlers installation */
void	set_prompt_signals(void);

/* Parent (shell) just before forking commands */
void	set_exec_signals_parent(void);

/* In child process immediately after fork */
void	set_exec_signals_child(void);

/* Utility to translate a waited child status into g_last_status */
void	update_status_from_wait(int status);

#endif /* SIGNALS_H */
