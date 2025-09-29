/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 01:20:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/09/28 04:42:26 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal_received;

void	signals_set_interactive(void);
void	signals_set_exec_parent(void);
void	signals_set_exec_child(void);
void	signals_set_heredoc(void);

#endif