/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:30:58 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/25 21:58:47 by jsurian42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int		exec_redirections(t_scmd *self);
int		exec_heredoc(t_exec_data *data);
void	exec_cleanup_heredocs(t_exec_data *data);

#endif
