/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsurian42 <jsurian@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:37:17 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/26 13:20:10 by jsurian          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	exec_pipe(t_list *self, t_exec_data *data)
{
	if (self->next)
	{
		if (pipe(data->fd.fd_pipe))
			return (1);
	}
	return (0);
}

int	exec_fork(t_scmd *self)
{
	self->pid = fork();
	if (self->pid == -1)
		return (1);
	return (0);
}

int	exec_pipeline(t_exec_data *data)
{
	t_list	*lst_current;

	lst_current = data->lst_simple_cmd;
	if (!lst_current->next && is_builtin(lst_current->scmd->argv[0]))
	{
		if (exec_simple_builtin(lst_current->scmd, data))
			return (1);
	}
	else
	{
		while (lst_current)
		{
			if (exec_pipe(lst_current, data))
				return (1);
			if (exec_fork(lst_current->scmd))
				return (1);
			if (exec_child(lst_current->scmd, data))
				return (1);
			if (exec_parent(lst_current, data))
				return (1);
			lst_current = lst_current->next;
		}
		exec_parent_wait(data);
	}
	return (0);
}
