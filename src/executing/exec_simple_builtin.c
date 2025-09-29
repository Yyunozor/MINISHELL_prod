/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:50:03 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	exec_restore_builtin(t_exec_data *data, int exit_status, int ret)
{
	data->exit_status = exit_status;
	dup2(data->fd.fd_saved_in, STDIN_FILENO);
	dup2(data->fd.fd_saved_out, STDOUT_FILENO);
	return (ret);
}

int	exec_simple_builtin(t_scmd *self, t_exec_data *data)
{
	self->exit_status = data->exit_status;
	self->is_interactive = data->is_interactive;
	if (exec_expansion(self))
		return (exec_restore_builtin(data, 1, 1));
	if (!self->argv || !self->argv[0])
		return (exec_restore_builtin(data, 0, 0));
	if (exec_redirections(self))
		return (exec_restore_builtin(data, 1, 1));
	data->exit_status = execute_builtin(self);
	data->envp = self->env;
	return (exec_restore_builtin(data, data->exit_status, 0));
}
