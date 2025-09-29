/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:54:28 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 08:15:36 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "heredoc_utils.h"

int	exec_heredoc_get_fd(t_red *red, char **envp, int exit_status)
{
	int			fd_pipe[2];
	t_heredoc_ctx	ctx;
	int			status;

	red->word = expand_remove_quote(red->word);
	if (red->word == NULL)
		return (1);
	if (pipe(fd_pipe))
		return (-1);
	ctx.fd_pipe = fd_pipe;
	ctx.envp = envp;
	ctx.exit_status = exit_status;
	ctx.delim_len = ft_strlen(red->word);
	signals_set_heredoc();
	status = heredoc_collect_lines(red, &ctx);
	if (status != 0)
		return (status);
	close(fd_pipe[1]);
	signals_set_interactive();
	return (fd_pipe[0]);
}

int	exec_heredoc_set_fd(t_red *red, char **envp, int exit_status)
{
	if (red->type == RED_HEREDOC)
	{
		red->fd_heredoc = exec_heredoc_get_fd(red, envp, exit_status);
		if (red->fd_heredoc == -1)
			return (1);
	}
	return (0);
}

int	exec_heredoc_set(t_scmd *self)
{
	size_t	i;

	i = 0;
	while (i < self->nbr_of_red)
	{
		if (exec_heredoc_set_fd(&self->red[i], self->env, self->exit_status))
			return (1);
		i++;
	}
	return (0);
}

int	exec_heredoc(t_exec_data *data)
{
	t_list	*lst_current;

	lst_current = data->lst_simple_cmd;
	while (lst_current)
	{
		lst_current->scmd->exit_status = data->exit_status;
		if (exec_heredoc_set(lst_current->scmd))
		{
			if (g_signal_received == SIGINT)
			{
				data->exit_status = 128 + SIGINT;
				g_signal_received = 0;
			}
			else
				data->exit_status = 1;
			return (1);
		}
		lst_current = lst_current->next;
	}
	return (0);
}
