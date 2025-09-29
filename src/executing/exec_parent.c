/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:15:20 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	exec_parent_signal_notice(t_list *current, int sig)
{
	if (current->next != NULL)
		return ;
	if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
	else if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

static void	exec_parent_status(t_exec_data *data, t_list *current, int status)
{
	int	sig;

	sig = 0;
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		exec_parent_signal_notice(current, sig);
		data->exit_status = 128 + sig;
	}
}

int	exec_parent_wait(t_exec_data *data)
{
	int		w_status;
	t_list	*lst_current;

	lst_current = data->lst_simple_cmd;
	while (lst_current)
	{
		if (waitpid(lst_current->scmd->pid, &w_status, 0))
			exec_parent_status(data, lst_current, w_status);
		lst_current = lst_current->next;
	}
	return (0);
}

int	exec_parent(t_list *self, t_exec_data *data)
{
	if (self->scmd->pid == 0)
		return (0);
	if (data->fd.fd_prev != -1)
	{
		close(data->fd.fd_prev);
		data->fd.fd_prev = -1;
	}
	if (data->fd.fd_pipe[1] != -1)
	{
		data->fd.fd_prev = data->fd.fd_pipe[0];
		close(data->fd.fd_pipe[1]);
		data->fd.fd_pipe[1] = -1;
	}
	if (self->next == NULL && data->fd.fd_pipe[0] != -1)
	{
		close(data->fd.fd_pipe[0]);
		data->fd.fd_pipe[0] = -1;
	}
	return (0);
}
