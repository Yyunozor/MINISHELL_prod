/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:32:39 by jsurian42         #+#    #+#             */
/*   Updated: 2025/09/29 10:22:45 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec_cleaning(t_exec_data *data)
{
	exec_cleanup_heredocs(data);
	ft_lstclear(&data->lst_simple_cmd, del_lst_scmd);
}

static void	exec_finalize(t_shell *shell, t_exec_data *data, int update_envp)
{
	if (update_envp)
		shell->envp = data->envp;
	shell->last_exit_status = data->exit_status;
	exec_cleaning(data);
	shell->head = NULL;
	signals_set_interactive();
}

int	executing(t_shell *shell)
{
	t_exec_data	data;

	if (shell->head == NULL)
		return (0);
	if (exec_init(&data, shell->head, shell->envp, shell->last_exit_status))
		return (1);
	data.is_interactive = shell->is_interactive;
	if (exec_heredoc(&data))
	{
		exec_finalize(shell, &data, 0);
		return (1);
	}
	signals_set_exec_parent();
	if (exec_pipeline(&data))
	{
		exec_finalize(shell, &data, 1);
		return (1);
	}
	exec_finalize(shell, &data, 1);
	return (0);
}
